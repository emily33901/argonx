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
    virtual void pad3()  = 0;
    virtual void pad4()  = 0;
    virtual void pad5()  = 0;
    virtual void pad6()  = 0;
    virtual void pad7()  = 0;
    virtual void pad8()  = 0;
    virtual void pad9()  = 0;
    virtual void pad10() = 0;

    virtual uptr GetAPICallFailureReason(unsigned long long) = 0;
};

Pipe *fakeServer;
Pipe *clientPipe;
void  ClientRpcPipe();

ISteamUtils009 *utils;

int main(const int argCount, const char **argStrings) {
    fakeServer                 = new Pipe(true, "tcp://127.0.0.1:33901", 33901);
    fakeServer->processMessage = [](Pipe::Handle h, u8 *data, u32 size) {
        printf("[serverpipe] size:%d\n", size);

        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        u64 jobId = b.Read<u64>();

        Steam::RpcCallHeader header;
        b.ReadInto(header);

        using DispatchFromBufferFn = void (*)(void *instance, u32 functionIndex, Buffer &);

        auto dispatch = Steam::RpcDispatches()[header.dispatchIndex];
        auto fn = (DispatchFromBufferFn)dispatch.first;

        printf("Dispatch:%s\n", dispatch.second);

        b.SetBaseAtCurPos();

        fn(((Steam::InterfaceHelpers::GenericAdaptor *)utils)->realThisptr, header.functionIndex, b);

        printf("Target:%s index:%d\n", Steam::interfaceNames[(u32)header.targetInterface], header.functionIndex);

        b = Buffer{};
        b.Write(jobId);
        b.Write<u64>(0xCCCCCCCCAABBAABB);
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

    utils = (ISteamUtils009 *)CreateInterface("SteamUtils009", nullptr);
    Assert(utils != nullptr, "CreateInterface test failed");

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

    auto r = utils->GetSecondsSinceAppActive();
    printf("r is %llX\n", r);
    r = utils->GetAPICallFailureReason(0xCCFFCCFFAABBAABB);
    printf("r is %llX\n", r);
    r = utils->GetSecondsSinceAppActive();
    printf("r is %llX\n", r);
    r = utils->GetSecondsSinceAppActive();
    printf("r is %llX\n", r);
    r = utils->GetSecondsSinceAppActive();
    printf("r is %llX\n", r);

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
