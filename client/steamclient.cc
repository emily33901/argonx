#include <algorithm>
#include <array>
#include <precompiled.hh>

#include "steamclient.hh"

#include "emsg.hh"
#include "language_internal.hh"
#include "steammessages_clientserver_login.pb.h"

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
        assert(0);
    }
}

Argonx::MsgBuilder::MsgBuilder(EMsg t, const google::protobuf::Message &message, u32 sessionId, SteamId steamId, u64 jobId) {
    CMsgProtoBufHeader proto;
    proto.set_steamid(steamId);
    proto.set_client_sessionid(sessionId);

    if (jobId) {
        proto.set_jobid_target(jobId);
    }

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

std::pair<const std::string, const std::string> SteamClient::FindServer() {
    auto addr = std::string(hardCodedCMList[rand() % hardCodedCMList.size()]);

    auto colonPos = std::find(addr.begin(), addr.end(), ':');
    *colonPos     = '\0';

    return std::make_pair(std::string(addr), std::string(++colonPos, addr.end()));
}

std::optional<TcpPacket> SteamClient::ReadPacket() {
    TcpPacket p;
    s.ReadStructure(p.header);

    if (!p.header.Valid()) return std::nullopt;

    std::vector<u8> temp;
    s.Read(temp, p.header.packetSize);

    if (encrypted) {
        Buffer t{temp};
        crypt.SymetricDecrypt(t, p.body);
    } else {
        p.body.Write(temp);
    }

    return p;
}

void SteamClient::HandleEncryptionHandshake(MsgHdr &h, TcpPacket &p) {
    using namespace CryptoPP;

    switch ((EMsg)h.msg) {
    case EMsg::ChannelEncryptRequest: {
        MsgChannelEncryptRequest r;
        r.FromBuffer(p.body);
        printf("proto: %d, universe: %d\n", r.protocolVersion, r.universe);

        MsgBuilder w{EMsg::ChannelEncryptResponse};

        auto &b = w.GetBody();
        b.Write(MsgChannelEncryptResponse{}.ToBuffer());

        crypt.GenerateSessionKey(b);

        WriteMessage(w);
    } break;
    case EMsg::ChannelEncryptResult: {
        MsgChannelEncryptResult r;
        r.FromBuffer(p.body);
        printf("result: %d\n", r.result);

        encrypted = r.result == 1;

        // TODO: Remove from here
        CMsgClientLogon logon;
        logon.set_account_name("username");
        logon.set_password("password");
        logon.set_protocol_version(65575);

        MsgBuilder b{EMsg::ClientLogon, logon, sessionId, steamId};

        WriteMessage(b);
    }
    default: {
    }
    }
}

bool SteamClient::ProcessPacket(TcpPacket &p) {
    printf("Processing packet...\n");

    p.body.SetPos(0);
    auto rawMessage = p.body.Read<u32>();
    p.body.SetPos(0);

    auto isProto = IsProto(rawMessage);
    auto message = RawMsg(rawMessage);

    printf("Packet size: %d\n", p.header.packetSize);
    printf("Message:     %d [%s] (%d)\n", message, isProto ? "p" : "", rawMessage);
    printf("Body length: %d\n", p.body.Size());

    if (!isProto) {
        switch (message) {
        case EMsg::ChannelEncryptRequest:
        case EMsg::ChannelEncryptResult: {
            printf("Encryption handshake\n");
            p.body.SetPos(0);

            auto hdr = MsgHdr{};
            hdr.FromBuffer(p.body);
            HandleEncryptionHandshake(hdr, p);
        } break;
        default: {
            ExtendedClientMsgHdr header;
            header.FromBuffer(p.body);

            printf("sessionId is %d\n", sessionId);
        } break;
        }
    } else {
        MsgHdrProtoBuf protoHeader;
        protoHeader.FromBuffer(p.body);

        printf("Header length: %d\n", protoHeader.headerLength);
    }

    return false;
}

void SteamClient::WriteMessage(MsgBuilder &b) {
    auto &body = b.GetBody();

    if (encrypted) crypt.SymetricEncrypt(body, body);

    printf("Final message size is %d\n", body.Size() + 8);

    // printf("\n");
    // for (auto v : body.Storage()) {
    //     printf("%d, ", v);
    // }
    // printf("\n");

    s.Write((u32)body.Storage().size());
    s.Write(0x31305456); // VT01 magic

    s.Write(body.Storage());
}
