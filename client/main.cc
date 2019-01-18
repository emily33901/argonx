#include "precompiled.hh"

#include "steamclient.hh"

int main(const int argCount, const char **argStrings) {
    Argonx::SteamClient sClient;

    printf("Pumping...\n");

    sClient.Run();

    return 0;
}
