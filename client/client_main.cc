#include <precompiled.hh>

#include <thread>

#include <cpptoml/include/cpptoml.h>

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

void CreateClientPipe(int rpcTimeout) {
    Steam::JobManager::SetResponseTimeout(rpcTimeout);
    Steam::SetClientPipe(new Pipe(false, "tcp://127.0.0.1:33901"));
    Steam::ClientPipe()->processMessage = [](Pipe::Target, u8 *data, u32 size) {
        LOG_SCOPE_F(INFO, "Client message");

        LOG_F(INFO, "size:%d", size);

        // Assume rpc job
        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        auto jobId = b.Read<i64>();

        if (jobId < 0) {
            LOG_F(INFO, "Recieved heartbeat response from server");
            auto header = b.Read<Steam::RpcNonCallHeader>();

            switch (header.t) {
            case Steam::RpcType::heartbeat: {
            } break;
            }
        } else {
            b.SetBaseAtCurPos();
            Steam::JobManager::PostResult(jobId, b);
        }
    };
}

// Since this is test code we are allowing ourselves to use this
#include "../steam/interfaces/steamplatform.hh"

namespace Reference {
using namespace Steam;
#include "SteamStructs/IClientEngine.h"
#include "SteamStructs/IClientUser.h"
} // namespace Reference

int main(int argCount, char **argStrings) {
    loguru::init(argCount, argStrings);

    loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);
    loguru::add_file("latest_readable.log", loguru::Truncate, loguru::Verbosity_INFO);

    // Only show most relevant things on stderr:
    loguru::g_stderr_verbosity = 1;

    LOG_F(INFO, "Waiting for server...");

    const auto cfg     = cpptoml::parse_file("argonx_client.toml");
    const auto timeout = cfg->get_qualified_as<int>("rpc.timeout");

    Assert(timeout, "Client config invalid!");

    CreateClientPipe(*timeout);
    bool        running = true;
    std::thread pipeThread{[&running]() {
        std::chrono::time_point<std::chrono::system_clock> lastHeartbeatSent;
        while (running) {
            Steam::ClientPipe()->ProcessMessages();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);

            if ((std::chrono::system_clock::now() - lastHeartbeatSent) > 20s) {
                auto b = Buffer{
                    Steam::JobManager::GetNextNonCallJobId(),
                    Steam::RpcNonCallHeader{Steam::RpcType::heartbeat},
                };
                b.SetPos(0);
                Steam::ClientPipe()->SendMessage(0, b.Read(0), b.Size());

                // Update the timepoints
                lastHeartbeatSent     = std::chrono::system_clock::now();
            }
        }
    }};

    auto *clientEngine = (Reference::IClientEngine *)Steam::CreateInterface("ClientEngine", nullptr);

    auto pipeHandle = clientEngine->CreateSteamPipe();
    auto userHandle = clientEngine->CreateLocalUser(&pipeHandle, Steam::EAccountType::k_EAccountTypeIndividual);

    bool isValid = clientEngine->IsValidHSteamUserPipe(pipeHandle, userHandle);

    LOG_F(INFO, "Are pipe and user valid: %s", isValid ? "Yes" : "No");

    auto *clientUser = (Reference::IClientUser *)clientEngine->GetIClientUser(userHandle, pipeHandle);
    LOG_F(INFO, "clientUser is null? %s", !clientUser ? "True" : "False");

    const auto username   = cfg->get_qualified_as<std::string>("login.username");
    const auto password   = cfg->get_qualified_as<std::string>("login.password");
    const auto twofactor  = cfg->get_qualified_as<std::string>("login.twofactor");
    const auto steamguard = cfg->get_qualified_as<std::string>("login.steamguard");

    Assert(username && password && twofactor && steamguard, "client config is invalid");

    clientUser->SetTwoFactorCode(twofactor->c_str());
    clientUser->Set2ndFactorAuthCode(steamguard->c_str(), false);

    clientUser->LogOnWithPassword(username->c_str(), password->c_str());

#if 1
    std::this_thread::sleep_for(std::chrono::seconds(60));
#endif

    clientUser->BConnected();

    clientEngine->ReleaseUser(pipeHandle, userHandle);
    clientEngine->BReleaseSteamPipe(pipeHandle);

    running = false;
    pipeThread.join();
}