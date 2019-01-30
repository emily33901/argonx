#include "precompiled.hh"

#include <thread>

#include "steamclient.hh"

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

class ISteamUtils009 {
public:
    virtual uptr GetSecondsSinceAppActive() = 0;

    virtual void pad0()  = 0;
    virtual void pad1()  = 0;
    virtual void pad2()  = 0;
    virtual const char *GetIPCountry() = 0;
    virtual void pad4()  = 0;
    virtual void pad5()  = 0;
    virtual void pad6()  = 0;
    virtual void pad7()  = 0;
    virtual void pad8()  = 0;
    virtual void pad9()  = 0;
    virtual void pad10() = 0;

    virtual uptr GetAPICallFailureReason(unsigned long long) = 0;

    virtual void pad11() = 0;
    virtual void pad12() = 0;
    virtual void pad13() = 0;
    virtual void pad14() = 0;
    virtual void pad15() = 0;
    virtual void pad16() = 0;

    virtual uptr CheckFileSignature(const char *) = 0;
};

ISteamUtils009 *utils;
extern void *   CreateServerClientUtils();

void *serverUtils = CreateServerClientUtils();

void CreateClientPipe() {
    Steam::SetClientPipe(new Pipe(false, "tcp://127.0.0.1:33901"));
    Steam::ClientPipe()->processMessage = [](Pipe::Target, u8 *data, u32 size) {
        printf("[clientpipe] size:%d\n", size);

        // Assume rpc job
        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        auto jobId = b.Read<u64>();
        b.SetBaseAtCurPos();
        Steam::JobManager::PostResult(jobId, b);
    };
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

        using DispatchFromBufferFn = Buffer (*)(void *instance, u32 functionIndex, Buffer &);

        auto dispatch = Steam::RpcDispatches()[header.dispatchIndex];
        auto fn       = (DispatchFromBufferFn)dispatch.first;

        printf("Dispatch:%s\n", dispatch.second);

        b.SetBaseAtCurPos();

        b = fn(serverUtils, header.functionIndex, b);

        printf("Target:%s index:%d\n", Steam::interfaceNames[(u32)header.targetInterface], header.functionIndex);

        b.SetPos(0);
        b.Write(jobId);
        b.SetPos(0);

        Steam::ServerPipe()->SendMessage(target, b.Read(0), b.Size());
    };
}

int main(const int argCount, const char **argStrings) {
    CreateServerPipe();
    std::thread serverThread{
        []() {
            while (true) {
                Steam::ServerPipe()->ProcessMessages();

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1ms);
            }
        }};

    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    extern void *CreateInterface(const char *name, int *err);

    utils = (ISteamUtils009 *)CreateInterface("SteamUtils009", nullptr);
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

    auto r = utils->GetSecondsSinceAppActive();
    printf("r is %llX\n", r);
    r = utils->GetAPICallFailureReason(0xCCFFCCFFAABBAABB);
    printf("r is %llX\n", r);
    r = utils->CheckFileSignature("wow nice meme");
    printf("r is %llX\n", r);
    const char *country = utils->GetIPCountry();
    printf("country is %s\n", country);

    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}

#include "../steam/rpc.hh"
