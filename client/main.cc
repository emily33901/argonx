#include "precompiled.hh"

#include "steamclient.hh"

int main(const int argCount, const char **argStrings) {
    SteamClient sClient;

    Socket    s("162.254.197.181", "27017");
    TcpHeader h;
    s.ReadStructure(h);

    printf("Read %s\n", std::string(h.magic, 4).c_str());
    return 0;
}
