#include "precompiled.hh"

#include "steamclient.hh"

#include "../steam/interfaces/helpers.hh"

int main(const int argCount, const char **argStrings) {
    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    extern void *CreateInterface(const char *name, int *err);

    auto a = CreateInterface("SteamUtils009", nullptr);
    Assert(a != nullptr, "CreateInterface test failed");

    extern Steam::InterfaceHelpers::InterfaceReg *GetInterfaceList();

    {
        auto head  = GetInterfaceList();
        auto total = 0;

        for (auto cur = head; cur != nullptr; cur = cur->next) {
            total += 1;
            printf("[I] %s\n", cur->name);
        }
    }
    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}
