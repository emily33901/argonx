#include "precompiled.hh"

#include "socket.hh"

const char *MAGIC      = "VT01";
uint32_t    PROTO_MASK = 0x80000000;

class SteamClient {
public:
    SteamClient(const char *addr) {
    }
};

int main(const int argCount, const char **argStrings) {

    Socket          s("162.254.197.181", "27017");
    std::vector<u8> data;
    s.Read(data, 8);

    printf("Read %s\n", &*(data.begin() + 4));
    return 0;
}
