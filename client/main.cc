#include "precompiled.hh"

#include "steamclient.hh"

#include "../steam/interfaces/helpers.hh"

int main(const int argCount, const char **argStrings) {
    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}
