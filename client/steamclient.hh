#pragma once

#include <optional>
#include <utility>

#include "buffer.hh"
#include "socket.hh"

#include "emsg.hh"

namespace Argonx {
class TcpHeader {
public:
    u32 packetSize;
    u32 magic;

    bool Valid() {
        // 'VT01'
        // 825250902
        return magic == 825250902;
    }
};

class TcpPacket {
public:
    TcpHeader header;
    Buffer    body;
    // std::vector<u8> body;
};

class MsgBuilder {
    bool isProto = false;

    Buffer body;

public:
    u32 msg;

    MsgBuilder(EMsg t);
    void    SetProto() { isProto = true; }
    Buffer &GetBody() { return body; }

    Buffer &Finish();
};

class SteamClient {
    u64 steamId;
    u32 sessionId;

    u8     sessionKey[32];
    bool   encrypted = false;
    u8     publicKey;
    Socket s;

    static std::pair<const std::string, const std::string> FindServer();

    void HandleEncryptionHandshake(struct MsgHdr &h, TcpPacket &p);

public:
    SteamClient() : s(SteamClient::FindServer()) {
    }

    std::optional<TcpPacket> ReadPacket();

    bool ProcessPacket(TcpPacket &p);

    void WriteMessage(MsgBuilder &b);
};
} // namespace Argonx
