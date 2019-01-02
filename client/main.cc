#include "precompiled.hh"

#include "steamclient.hh"

int main(const int argCount, const char **argStrings) {
    Argonx::SteamClient sClient;

    auto i = 0;
    while (i < 4) {
        auto p = sClient.ReadPacket();

        if (p.has_value()) {
            sClient.ProcessPacket(p.value());
        }

        ++i;
    }

    // sClient.ProcessPacket(p);

    // printf("Read %s\n", std::string(h.magic, 4).c_str());
    return 0;
}
