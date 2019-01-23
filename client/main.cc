#include "precompiled.hh"

#include <thread>

#include "steamclient.hh"

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

Pipe *p;
Pipe *p2;

u8 data[] = {
    0xFF,
    0xFF,
    0xFF,
    0xFF,
};

int main(const int argCount, const char **argStrings) {
    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    extern void *CreateInterface(const char *name, int *err);

    auto a = CreateInterface("SteamUtils009", nullptr);
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

    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}

void TestPipes() {

    p                 = new Pipe(true, "tcp://127.0.0.1:33901", 33901);
    p->processMessage = [](u8 *data, u32 size) {
        printf("[serverpipe] size:%d\n", size);
    };

    bool done = false;

    std::thread serverPipe{
        [&done]() {
            while (!done) {
                p->ProcessMessages();

                if (p->PipeCount() > 0)
                    p->SendMessage(1, data, rand() % 2 ? 3 : 4);

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ms);
            }
        }};

    p2                 = new Pipe(false, "tcp://127.0.0.1:33901");
    p2->processMessage = [](u8 *data, u32 size) {
        printf("[clientpipe] size:%d\n", size);
    };

    std::thread clientPipe{
        [&done]() {
            while (!done) {
                p2->ProcessMessages();
                p2->SendMessage(0, data, rand() % 2 ? 3 : 4);

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);
            }
        }};
}
