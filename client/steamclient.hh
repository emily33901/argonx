#pragma once

#include <utility>

#include "socket.hh"

class TcpHeader {
public:
    u32 packetSize;
    u32 magic;

    bool Valid() {
        // 'VT01'
        // 1448357937
        return magic == 1448357937;
    }
};

class TcpPacket {
public:
    TcpHeader       header;
    std::vector<u8> body;
};

class SteamClient {
    u64 steamId;
    u32 sessionId;

    u8     sessionKey[32];
    bool   encrypted = false;
    u8     publicKey;
    Socket s;

    static std::pair<const std::string, const std::string> FindServer();

public:
    SteamClient() : s(SteamClient::FindServer()) {
    }

    bool ReadPacket() {
        TcpPacket p;
        s.ReadStructure(p.header);

        if (!p.header.Valid()) return false;

        s.Read(p.body, p.header.packetSize);

        return true;
    }
};
