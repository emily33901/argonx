#include <precompiled.hh>

#include <thread>

#include <cpptoml/include/cpptoml.h>

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

std::chrono::time_point<std::chrono::system_clock> lastHeartbeatResponse;

void CreateClientPipe(int rpcTimeout) {
    Steam::JobManager::SetResponseTimeout(rpcTimeout);
    Steam::SetClientPipe(new Pipe(false, "tcp://127.0.0.1:33901"));
    Steam::ClientPipe()->processMessage = [](Pipe::Target, u8 *data, u32 size) {
        printf("[clientpipe] size:%d\n", size);

        // Assume rpc job
        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        auto jobId = b.Read<i64>();

        if (jobId < 0) {
            printf("Recieved heartbeat response from server\n");
            auto header = b.Read<Steam::RpcNonCallHeader>();

            switch (header.t) {
            case Steam::RpcType::heartbeat: {
                lastHeartbeatResponse = std::chrono::system_clock::now();
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

int main(const int argCount, const char **argStrings) {
    printf("Waiting for server...\n");

    const auto cfg = cpptoml::parse_file("argonx_client.toml");
    const auto       timeout = cfg->get_qualified_as<int>("rpc.timeout");

    Assert(timeout, "Client config invalid!");

    CreateClientPipe(*timeout);
    bool        running = true;
    std::thread pipeThread{[&running]() {
        std::chrono::time_point<std::chrono::system_clock> lastHeartbeatSent{};
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
                lastHeartbeatResponse = lastHeartbeatSent;
            } else if (lastHeartbeatSent == lastHeartbeatResponse &&
                       std::chrono::system_clock::now() - lastHeartbeatResponse > 15s) {
                // Server died?

                // In this senario steam client sends and IpcFailure_t and the client is expected
                // to reset their steam data and attempt to reconnect
                // so there is nothing more that we need to do after that.
                // ... Although it is more likely that the Rpc will figure that out first!

                printf("Server is probably dead!\n");
            }
        }
    }};

    auto *clientEngine = (Reference::IClientEngine *)Steam::CreateInterface("ClientEngine", nullptr);

    auto pipeHandle = clientEngine->CreateSteamPipe();
    auto userHandle = clientEngine->CreateLocalUser(&pipeHandle, Steam::EAccountType::k_EAccountTypeIndividual);

    bool isValid = clientEngine->IsValidHSteamUserPipe(pipeHandle, userHandle);

    printf("Are pipe and user valid: %s\n", isValid ? "Yes" : "No");

    auto *clientUser = (Reference::IClientUser *)clientEngine->GetIClientUser(userHandle, pipeHandle);
    printf("clientUser is null? %s\n", !clientUser ? "True" : "False");

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

#if 0
    // Using the steamclient interface
    void *clientUtils = Steam::CreateInterfaceWithUser("SteamUtils009", 15);
    auto  utils       = (ISteamUtils009 *)clientUtils;

    uptr r;
    r = utils->GetSecondsSinceAppActive();
    printf("r is %ld\n", r);
    r = utils->GetAPICallFailureReason(0xCCFFCCFFAABBAABB);
    printf("r is %ld\n", r);

    r = utils->CheckFileSignature("wow nice meme");
    printf("r is %ld\n", r);

    const char *country = utils->GetIPCountry();
    printf("country is %s\n", country);
    u32 w, h;
    utils->GetImageSize(0, &w, &h);
    printf("w is %d, h is %d\n", w, h);

    u8 buffer[10];
    memset(buffer, 0xDE, sizeof(buffer));
    utils->GetImageRGBA(15, buffer, 10);
    buffer[9] = '\0';
    printf("Buffer is \"%s\"\n", buffer);

#endif

    running = false;
    pipeThread.join();
}