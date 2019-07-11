#include <precompiled.hh>

#include <thread>

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

void CreateClientPipe() {
    Steam::SetClientPipe(new Pipe(false, "tcp://127.0.0.1:33901"));
    Steam::ClientPipe()->processMessage = [](Pipe::Target, u8 *data, u32 size) {
        printf("[clientpipe] size:%d\n", size);

        // Assume rpc job
        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        auto jobId = b.Read<i64>();

        if (jobId < 0) {
            auto header = b.Read<Steam::RpcNonCallHeader>();

            switch (header.t) {
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
    CreateClientPipe();
    bool        running = true;
    std::thread pipeThread{[&running]() {
        std::chrono::time_point<std::chrono::system_clock> t{};
        while (running) {
            Steam::ClientPipe()->ProcessMessages();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);

            if ((std::chrono::system_clock::now() - t) > 20s) {
                auto b = Buffer{
                    Steam::JobManager::GetNextNonCallJobId(),
                    Steam::RpcNonCallHeader{Steam::RpcType::heartbeat},
                };
                b.SetPos(0);
                Steam::ClientPipe()->SendMessage(0, b.Read(0), b.Size());

                t = std::chrono::system_clock::now();
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

    clientUser->BConnected();

    clientEngine->ReleaseUser(pipeHandle, userHandle);
    clientEngine->BReleaseSteamPipe(pipeHandle);

#if 0
    // TODO: we need to be able to ask the server for a userhandle and a pipe first
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