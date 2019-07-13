#pragma once

#include <optional>
#include <utility>

#include "buffer.hh"
#include "socket.hh"

#include "scheduledfunction.hh"

#include "emsg.hh"
#include "steamid.hh"

#include "steamcrypt.hh"

namespace google::protobuf {
class Message;
}

namespace Argonx {
class CMClient;

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
    MsgBuilder(EMsg t, const google::protobuf::Message &message, CMClient *c, u64 jobId = 0);

    Buffer &GetBody() { return body; }
};

class CMClient {
    bool      encrypted = false;
    Socket    s;
    TcpHeader nextPacketHeader;

    // Queue of messages until we are encrypted
    std::vector<MsgBuilder> msgQueue;

    static std::pair<const std::string, const std::string> FindServer();

    void HandleEncryptionHandshake(struct MsgHdr &h, TcpPacket &p);

    void SendClientHeartbeat();

public:
    // Handlers
    static void HandleMultiMessage(CMClient *s, size_t msgSize, Buffer &b, u64 jobId);
    static void HandleEncryptionRequest(CMClient *s, size_t msgSize, Buffer &b, u64 jobId);
    static void HandleEncryptionResult(CMClient *s, size_t msgSize, Buffer &b, u64 jobId);

public:
    SteamId           steamId;
    u32               sessionId = 0;
    SteamCrypt        crypt;
    ScheduledFunction clientHeartbeatFunction;

public:
    CMClient() : s(CMClient::FindServer()), clientHeartbeatFunction([this]() { SendClientHeartbeat(); }) {
        steamId.instance = 1;
        steamId.universe = static_cast<unsigned>(EUniverse::Public);
        steamId.type     = static_cast<unsigned>(EAccountType::Individual);
    }

    std::optional<TcpPacket> ReadPacket();
    bool                     ProcessPacket(TcpPacket &p);

    void Run(const bool &run = true);

    void WriteMessage(MsgBuilder &b);
    void WriteMessage(EMsg t, const ::google::protobuf::Message &message, u64 jobId = 0);

    void ResetClientHeartbeat(std::chrono::milliseconds delay);
    void TryAnotherCM();

private:
    void SetEncrypted(bool t) { encrypted = t; }
    void SendQueuedMessages();
};
} // namespace Argonx
