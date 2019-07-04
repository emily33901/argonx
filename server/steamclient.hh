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

class CMClient {

    bool   encrypted = false;
    Socket s;

    static std::pair<const std::string, const std::string> FindServer();

    void HandleEncryptionHandshake(struct MsgHdr &h, TcpPacket &p);

public:
    SteamId    steamId;
    u32        sessionId = 0;
    SteamCrypt crypt;

public:
    CMClient() : s(CMClient::FindServer()) {
        steamId.instance = 1;
        steamId.universe = static_cast<unsigned>(EUniverse::Public);
        steamId.type     = static_cast<unsigned>(EAccountType::Individual);
    }

    std::optional<TcpPacket> ReadPacket();
    bool                     ProcessPacket(TcpPacket &p);

    void Run();

    void SetEncrypted(bool t) { encrypted = t; }

    void WriteMessage(MsgBuilder &b);
    void TryAnotherCM();
};
} // namespace Argonx
