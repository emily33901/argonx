#include "precompiled.hh"

#include <thread>

#include "steamclient.hh"

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

class ISteamUtils009 {
public:
    virtual uptr GetSecondsSinceAppActive() = 0;
};

Pipe *fakeServer;
Pipe *clientPipe;
void  ClientRpcPipe();

int main(const int argCount, const char **argStrings) {
    fakeServer                 = new Pipe(true, "tcp://127.0.0.1:33901", 33901);
    fakeServer->processMessage = [](Pipe::Handle h, u8 *data, u32 size) {
        printf("[serverpipe] size:%d\n", size);

        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        u64 jobId = b.Read<u64>();

        b.Write<u32>(0xCCCCCCCC);
        b.SetPos(0);

        fakeServer->SendMessage(h, b.Read(0), b.Size());
    };

    std::thread serverThread{
        []() {
            while (true) {
                fakeServer->ProcessMessages();

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1ms);
            }
        }};

    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    extern void *CreateInterface(const char *name, int *err);

    ISteamUtils009 *a = (ISteamUtils009 *)CreateInterface("SteamUtils009", nullptr);
    Assert(a != nullptr, "CreateInterface test failed");

    {
        extern Steam::InterfaceHelpers::InterfaceReg *GetInterfaceList();

        auto head  = GetInterfaceList();
        auto total = 0;

        for (auto cur = head; cur != nullptr; cur = cur->next) {
            total += 1;
            printf("[I] %s\n", cur->name);
        }

        printf("[I] %d total interfaces\n", total);
    }

    ClientRpcPipe();
    std::thread pipeThread{[]() {
        while (true) {
            clientPipe->ProcessMessages();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
    }};

    a->GetSecondsSinceAppActive();
    a->GetSecondsSinceAppActive();
    a->GetSecondsSinceAppActive();
    a->GetSecondsSinceAppActive();

    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}

#include "../steam/rpc.hh"

void ClientRpcPipe() {
    clientPipe                 = new Pipe(false, "tcp://127.0.0.1:33901");
    clientPipe->processMessage = [](Pipe::Handle, u8 *data, u32 size) {
        printf("[clientpipe] size:%d\n", size);

        // Assume rpc job
        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        auto jobId = b.Read<u64>();
        b.SetBaseAtCurPos();
        Steam::Jobs()->PostResult(jobId, b);
    };
}
