#pragma once

#include <optional>
#include <utility>

#include "buffer.hh"
#include "socket.hh"

#include "emsg.hh"
#include "steamid.hh"

#include "steamcrypt.hh"

namespace google::protobuf {
class Message;
}

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
    MsgBuilder(EMsg t, const google::protobuf::Message &message, u32 sessionId, SteamId steamId, u64 jobId = 0);
    Buffer &GetBody() { return body; }
};

class SteamClient {
    SteamId steamId;
    u32     sessionId = 0;

    bool       encrypted = false;
    SteamCrypt crypt;

    Socket s;

    static std::pair<const std::string, const std::string> FindServer();

    void HandleEncryptionHandshake(struct MsgHdr &h, TcpPacket &p);

public:
    SteamClient() : s(SteamClient::FindServer()) {
        steamId.instance = 1;
        steamId.universe = static_cast<unsigned>(EUniverse::Public);
        steamId.type     = static_cast<unsigned>(EAccountType::Individual);
    }

    std::optional<TcpPacket> ReadPacket();
    bool                     ProcessPacket(TcpPacket &p);

    void WriteMessage(MsgBuilder &b);
};
} // namespace Argonx
