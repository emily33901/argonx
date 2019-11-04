#include <algorithm>
#include <array>
#include <precompiled.hh>

#include "platform.hh"

#include "cmclient.hh"

#include "emsg.hh"
#include "language_internal.hh"
#include "steamhandlers.hh"
#include "steammessages_clientserver_login.pb.h"
#include "zip.hh"

using namespace Argonx;

constexpr u32 PROTO_MASK = 0x80000000;

static bool IsProto(u32 raw) {
    return (raw & PROTO_MASK) == PROTO_MASK;
}

static EMsg RawMsg(u32 full) {
    return (EMsg)(full & ~PROTO_MASK);
}

Argonx::MsgBuilder::MsgBuilder(EMsg t) {
    msg = (u32)t;

    if (msg == EMsg::ChannelEncryptResponse) {
        MsgHdr header{};
        header.msg = msg;
        body.Write(header.ToBuffer());

        body.SetPos(0);
        body.SeekBase<MsgHdr>();
    } else {
        Assert(0, "MsgBuilder(EMsg) should never get called for anything that isnt ChannelEncryptResponse");
    }
}

Argonx::MsgBuilder::MsgBuilder(EMsg t, const google::protobuf::Message &message, u32 sessionId, SteamId steamId, u64 jobId) {
    CMsgProtoBufHeader proto;
    proto.set_steamid(steamId);
    proto.set_client_sessionid(sessionId);

    if (jobId) proto.set_jobid_target(jobId);

    auto protoSize   = proto.ByteSize();
    auto messageSize = message.ByteSize();

    auto protoHeader         = MsgHdrProtoBuf{};
    protoHeader.msg          = t | PROTO_MASK;
    protoHeader.headerLength = protoSize;

    body.Write(protoHeader.ToBuffer());
    body.Fill(0, protoSize + messageSize);

    u8 *pos = body.Read(0);

    proto.SerializeToArray(pos, protoSize);
    message.SerializeToArray(pos + protoSize, messageSize);
}

Argonx::MsgBuilder::MsgBuilder(EMsg t, const google::protobuf::Message &message, CMClient *c, u64 jobId) : MsgBuilder(t, message, c->sessionId, c->steamId, jobId) {
}

static std::array hardCodedCMList = {
    "162.254.196.84:27018",
    "162.254.196.67:27019",
    "162.254.196.68:27019",
    "162.254.196.68:27018",
    "162.254.196.83:27017",
    "162.254.196.67:27018",
    "162.254.196.68:27017",
    "162.254.196.84:27019",
    "162.254.196.83:27018",
    "162.254.196.84:27017",
    "162.254.196.67:27017",
    "162.254.196.83:27019",
    "155.133.248.51:27017",
    "155.133.248.52:27019",
    "155.133.248.50:27017",
    "155.133.248.53:27018",
    "155.133.248.52:27017",
    "155.133.248.53:27019",
    "155.133.248.53:27017",
    "155.133.248.50:27019",
    "155.133.248.52:27018",
    "155.133.248.51:27018",
    "155.133.248.50:27018",
    "155.133.248.51:27019",
    "162.254.192.101:27017",
    "162.254.192.100:27018",
    "162.254.192.109:27017",
    "162.254.192.100:27017",
    "162.254.192.109:27018",
    "162.254.192.101:27018",
    "162.254.192.109:27019",
    "162.254.192.100:27019",
    "162.254.192.108:27019",
    "162.254.192.101:27019",
    "162.254.192.108:27018",
    "162.254.192.108:27017",
    "155.133.246.69:27017",
    "155.133.246.68:27019",
    "155.133.246.69:27019",
    "155.133.246.68:27018",
    "155.133.246.68:27017",
    "146.66.152.11:27017",
    "155.133.246.69:27018",
    "162.254.197.180:27017",
    "146.66.152.11:27019",
    "162.254.197.42:27019",
    "162.254.197.181:27019",
    "146.66.152.11:27018",
    "146.66.152.10:27018",
    "162.254.197.181:27018",
    "162.254.197.180:27019",
    "162.254.197.40:27019",
    "146.66.152.10:27017",
    "185.25.180.14:27018",
    "155.133.242.8:27019",
    "185.25.180.14:27019",
    "162.254.197.40:27018",
    "146.66.152.10:27019",
    "162.254.197.42:27017",
    "185.25.180.15:27019",
    "155.133.242.9:27019",
    "162.254.197.42:27018",
    "162.254.197.180:27018",
    "155.133.242.9:27018",
    "155.133.242.9:27017",
    "162.254.197.181:27017",
    "185.25.180.15:27017",
    "155.133.242.8:27017",
    "155.133.242.8:27018",
    "185.25.180.15:27018",
    "185.25.180.14:27017",
    "162.254.197.40:27017",
    "162.254.193.47:27017",
    "162.254.193.47:27018",
    "162.254.193.47:27019",
    "162.254.193.46:27017",
    "162.254.193.6:27019",
    "162.254.193.46:27019",
    "162.254.193.6:27017",
    "162.254.193.7:27017",
    "162.254.193.46:27018",
    "162.254.193.6:27018",
    "162.254.193.7:27018",
    "162.254.193.7:27019",
    "155.133.254.132:27018",
    "155.133.254.132:27017",
    "155.133.254.133:27018",
    "155.133.254.133:27019",
    "155.133.254.132:27019",
    "155.133.254.133:27017",
    "162.254.195.45:27017",
    "162.254.195.45:27018",
    "162.254.195.46:27018",
    "162.254.195.47:27017",
    "162.254.195.44:27019",
    "162.254.195.46:27019",
    "162.254.195.44:27017",
    "162.254.195.44:27018",
    "162.254.195.47:27018",
    "205.196.6.75:27018",
    "162.254.195.45:27019",
    "162.254.195.47:27019",
    "162.254.195.46:27017",
    "205.196.6.75:27017",
    "205.196.6.75:27019",
    "155.133.229.251:27017",
    "155.133.229.250:27018",
    "155.133.229.250:27019",
    "155.133.229.251:27019",
    "155.133.229.251:27018",
    "155.133.229.250:27017",
    "155.133.230.50:27017",
    "155.133.230.50:27019",
    "155.133.230.34:27019",
    "155.133.230.50:27018",
    "155.133.230.34:27018",
    "155.133.230.34:27017",
    "205.196.6.67:27019",
    "205.196.6.67:27017",
    "205.196.6.67:27018",
    "155.133.245.36:27019",
    "155.133.245.36:27018",
    "155.133.245.36:27017",
    "155.133.245.37:27019",
    "155.133.245.37:27017",
    "155.133.245.37:27018",
    "153.254.86.143:27017",
    "153.254.86.143:27018",
    "153.254.86.143:27019",
    "153.254.86.142:27017",
    "153.254.86.142:27019",
    "153.254.86.142:27018",
    "103.10.124.164:27017",
    "103.10.124.163:27019",
    "103.10.124.163:27018",
    "103.10.124.165:27018",
    "103.10.124.162:27018",
    "103.10.124.162:27017",
    "103.10.124.163:27017",
    "103.10.124.164:27018",
    "103.10.124.164:27019",
    "103.10.124.162:27019",
    "103.10.124.165:27019",
    "103.10.124.165:27017",
    "155.133.238.165:27017",
    "155.133.238.165:27019",
    "155.133.238.165:27018",
    "155.133.238.164:27017",
    "155.133.238.164:27018",
    "155.133.238.164:27019",
    "155.133.227.12:27019",
    "155.133.227.11:27018",
    "155.133.227.11:27019",
    "155.133.227.12:27018",
    "155.133.227.12:27017",
    "155.133.227.11:27017",
    "203.80.149.68:27017",
    "203.80.149.104:27019",
    "203.80.149.67:27017",
    "203.80.149.68:27018",
    "203.80.149.67:27018",
    "203.80.149.104:27018",
    "203.80.149.68:27019",
    "203.80.149.67:27019",
    "203.80.149.104:27017",
    "180.101.192.199:27019",
    "180.101.192.199:27018",
    "180.101.192.199:27017",
    "180.101.192.200:27017",
    "180.101.192.200:27019",
    "180.101.192.200:27018",
};

std::pair<const std::string, const std::string> CMClient::FindServer() {
    auto addr = std::string(hardCodedCMList[rand() % hardCodedCMList.size()]);

    auto colonPos = std::find(addr.begin(), addr.end(), ':');
    *colonPos     = '\0';

    return std::make_pair(std::string(addr), std::string(++colonPos, addr.end()));
}

std::optional<TcpPacket> CMClient::ReadPacket() {
    TcpPacket p;
    if (!nextPacketHeader.Valid()) {
        if (!s.ReadStructure(p.header)) return std::nullopt;
        if (!p.header.Valid()) return std::nullopt;

        nextPacketHeader = p.header;
    } else {
        p.header = nextPacketHeader;
    }

    std::vector<u8> temp;
    if (!s.Read(temp, p.header.packetSize)) return std::nullopt;

    if (encrypted) {
        Buffer t{temp};
        crypt.SymetricDecrypt(t, p.body);
    } else {
        p.body.Write(temp);
    }

    // Make it invalid to force a new read
    nextPacketHeader.magic = 0;

    return p;
}

bool CMClient::ProcessPacket(TcpPacket &p) {
    LOG_SCOPE_F(INFO, "Process Packet");

    p.body.SetPos(0);
    auto rawMessage = p.body.Read<u32>();
    p.body.SetPos(0);

    auto isProto = IsProto(rawMessage);
    auto message = RawMsg(rawMessage);

    LOG_F(INFO, "msg:%s%d size:%d bsize:%lu", isProto ? "p" : "", message, p.header.packetSize, p.body.Size());

    u64 jobId;
    u32 msgSize;

    if (!isProto) {
        // Header processing
        if (message == EMsg::ChannelEncryptRequest || message == EMsg::ChannelEncryptResult) {
            MsgHdr h;
            h.FromBuffer(p.body);
            p.body.SetBaseAtCurPos();
            jobId = h.sourceJobID;
        } else {
            ExtendedClientMsgHdr h;
            h.FromBuffer(p.body);
            p.body.SetBaseAtCurPos();
            jobId = h.sourceJobID;
        }

        msgSize = p.body.Size();

    } else {
        MsgHdrProtoBuf msgHeader;
        msgHeader.FromBuffer(p.body);
        // LOG_F(INFO, "Header length: %d", msgHeader.headerLength);

        CMsgProtoBufHeader protoHeader;
        protoHeader.ParseFromArray(p.body.Read(msgHeader.headerLength), msgHeader.headerLength);
        if (!sessionId && msgHeader.headerLength > 0) {
            sessionId = protoHeader.client_sessionid();
            steamId   = protoHeader.steamid();
        }

        jobId   = protoHeader.jobid_source();
        msgSize = (u32)p.body.SizeNoBase() - (u32)sizeof(MsgHdrProtoBuf) - msgHeader.headerLength;
    }

    SteamMessageHandler::ProcessMessage(this, message, msgSize, p.body, jobId);

    return false;
}

void CMClient::TryAnotherCM() {
    LOG_F(INFO, "Trying another CM...");
    SetEncrypted(false);
    auto newSocket = Socket(FindServer());
    s              = std::move(newSocket);
}

void CMClient::Run(const bool &run) {
    // TODO: some I/O functions are now non-blocking!
    // So we should be able to change this behaviour!
    while (run) {
        RunFrame();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    LOG_F(INFO, "====> Run exited");
}

void CMClient::RunFrame() {
    std::optional<Argonx::TcpPacket> p;

    // Read and process all the avaliable packets
    // and then return
    do {
        p = ReadPacket();
        if (p) ProcessPacket(*p);
    } while (p);
}

void CMClient::WriteMessage(MsgBuilder &b) {
    auto &body = b.GetBody();

    if (encrypted) {
        crypt.SymetricEncrypt(body, body);
    } else if (RawMsg(b.msg) != EMsg::ChannelEncryptRequest) {
        msgQueue.push_back(b);
        return;
    }

    s.Write((u32)body.Storage().size());
    s.Write(0x31305456); // VT01 magic

    s.Write(body.Storage());
}

void CMClient::WriteMessage(EMsg t, const ::google::protobuf::Message &message, u64 jobId) {
    MsgBuilder b{t, message, this, jobId};
    WriteMessage(b);
}

void CMClient::SendClientHeartbeat() {
    LOG_F(INFO, "Sending heartbeat to steam!");
    MsgBuilder b{EMsg::ClientHeartBeat, CMsgClientHeartBeat{}, sessionId, steamId};
    WriteMessage(b);
}

void CMClient::ResetClientHeartbeat(std::chrono::milliseconds d) {
    using namespace std::chrono_literals;
    LOG_F(INFO, "Out of game heartbeat is %llums", d.count());
    clientHeartbeatFunction.Stop();
    if (d > 0ms) {
        clientHeartbeatFunction.Delay(d);
        clientHeartbeatFunction.Start();
    }
}
void CMClient::SendQueuedMessages() {
    for (auto &m : msgQueue) {
        WriteMessage(m);
    }
    msgQueue.clear();
}
