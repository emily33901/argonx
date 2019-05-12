#include "precompiled.hh"

#include <thread>

#include "steamclient.hh"

#include "../steam/interfaces/helpers.hh"

extern void *CreateServerClientUtils();

void *serverUtils = CreateServerClientUtils();

void *noUserInterfaceStorage[(u32)Steam::InterfaceTarget::max];
void  CreateNoUserInterfaceStorage() {
    void *r[] = {
        nullptr,                                               // user
        nullptr,                                               // appList
        nullptr,                                               // apps
        nullptr,                                               // client
        Steam::CreateInterface("ServerClientEngine", nullptr), // engine
        nullptr,                                               // controller
        nullptr,                                               // friends
        nullptr,                                               // gameserver
        nullptr,                                               // remotestorage
        nullptr,                                               // ugc
        nullptr,                                               // userstats
        nullptr,                                               // utils

        nullptr, // argon
    };

    memcpy(noUserInterfaceStorage, r, sizeof(r));
}

void CreateServerPipe() {
    Steam::SetServerPipe(new Pipe(true, "tcp://127.0.0.1:33901", 33901));
    Steam::ServerPipe()->processMessage = [](Pipe::Target target, u8 *data, u32 size) {
        printf("[serverpipe] size:%d\n", size);

        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        u64 jobId = b.Read<u64>();

        Steam::RpcCallHeader header;
        b.ReadInto(header);

        printf("userHandle:%d\n", header.userHandle);

        void *instance = nullptr;

        if (header.userHandle == ~0) {
            // TODO: function for this
            instance = noUserInterfaceStorage[(u32)header.targetInterface];
        } else {
            instance = Steam::GetUserInterface((Steam::UserHandle)header.userHandle, header.targetInterface);
        }

        using DispatchFromBufferFn = Buffer (*)(void *instance, u32 functionIndex, Buffer &);

        auto dispatch = Steam::RpcDispatches()[header.dispatchIndex];
        auto fn       = (DispatchFromBufferFn)dispatch.first;

        b.SetBaseAtCurPos();

        b = fn(instance, header.functionIndex, b);

        printf("Target:%s index:%d\n", Steam::InterfaceName(header.targetInterface), header.functionIndex);

        b.SetPos(0);
        b.Write(jobId);
        b.SetPos(0);

        Steam::ServerPipe()->SendMessage(target, b.Read(0), b.Size());
    };

    // TODO: Handle clientconnected / disconnected
}

int main(const int argCount, const char **argStrings) {
    CreateNoUserInterfaceStorage();

    CreateServerPipe();
    std::thread serverThread{
        []() {
            while (true) {
                Steam::ServerPipe()->ProcessMessages();

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1ms);
            }
        }};

#if 0

    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    utils = (ISteamUtils009 *)Steam::CreateInterfaceWithUser("SteamUtils009", 0);
    Assert(utils != nullptr, "CreateInterface test failed");

    {
        u32 counter = 0;
        for (auto &p : Steam::RpcDispatches()) {
            printf("%d: %s\n", counter++, Platform::DemangleName(p.second));
        }
    }

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

    CreateClientPipe();
    std::thread pipeThread{[]() {
        while (true) {
            Steam::ClientPipe()->ProcessMessages();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
    }};
#endif

    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}

#include "../steam/rpc.hh"
