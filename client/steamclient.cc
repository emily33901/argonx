#include <algorithm>
#include <array>
#include <precompiled.hh>

#include "steamclient.hh"

using namespace Argonx;

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

    printf("%d, %s\n", p.header.magic, std::string((const char *)&p.header.magic, 4).c_str());

    if (!p.header.Valid()) return std::nullopt;

    std::vector<u8> temp;

    s.Read(temp, p.header.packetSize);

    printf("Writing to buffer body...\n");

    p.body.Write(temp);

    return p;
}

constexpr u32 PROTO_MASK = 0x80000000;

static bool IsProto(u32 raw) {
    return (raw & PROTO_MASK) == PROTO_MASK;
}

#include "emsg.hh"
#include "language_internal.hh"

Argonx::MsgBuilder::MsgBuilder(EMsg t) {
    msg = (u32)t;

    body.Write(std::make_pair((const char *)"VT01", 4));
    body.SetBase(4);
    body.SetPos(0);

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

Buffer &MsgBuilder::Finish() {
    body.SetBase(0);
    body.SetPos(0);

    auto size = body.SizeNoBase() - 8;

    body.Write<u32>(size);

    return body;
}

static EMsg RawMsg(u32 full) {
    return (EMsg)(full & ~PROTO_MASK);
}

#include <cryptopp/modes.h>

// clang-format off
u8 PUBLIC_KEY[] = {
    0x30, 0x81, 0x9D, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01,
    0x05, 0x00, 0x03, 0x81, 0x8B, 0x00, 0x30, 0x81, 0x87, 0x02, 0x81, 0x81, 0x00, 0xDF, 0xEC, 0x1A,
    0xD6, 0x2C, 0x10, 0x66, 0x2C, 0x17, 0x35, 0x3A, 0x14, 0xB0, 0x7C, 0x59, 0x11, 0x7F, 0x9D, 0xD3,
    0xD8, 0x2B, 0x7A, 0xE3, 0xE0, 0x15, 0xCD, 0x19, 0x1E, 0x46, 0xE8, 0x7B, 0x87, 0x74, 0xA2, 0x18,
    0x46, 0x31, 0xA9, 0x03, 0x14, 0x79, 0x82, 0x8E, 0xE9, 0x45, 0xA2, 0x49, 0x12, 0xA9, 0x23, 0x68,
    0x73, 0x89, 0xCF, 0x69, 0xA1, 0xB1, 0x61, 0x46, 0xBD, 0xC1, 0xBE, 0xBF, 0xD6, 0x01, 0x1B, 0xD8,
    0x81, 0xD4, 0xDC, 0x90, 0xFB, 0xFE, 0x4F, 0x52, 0x73, 0x66, 0xCB, 0x95, 0x70, 0xD7, 0xC5, 0x8E,
    0xBA, 0x1C, 0x7A, 0x33, 0x75, 0xA1, 0x62, 0x34, 0x46, 0xBB, 0x60, 0xB7, 0x80, 0x68, 0xFA, 0x13,
    0xA7, 0x7A, 0x8A, 0x37, 0x4B, 0x9E, 0xC6, 0xF4, 0x5D, 0x5F, 0x3A, 0x99, 0xF9, 0x9E, 0xC4, 0x3A,
    0xE9, 0x63, 0xA2, 0xBB, 0x88, 0x19, 0x28, 0xE0, 0xE7, 0x14, 0xC0, 0x42, 0x89, 0x02, 0x01, 0x11,
};
// clang-format on

#include <cryptopp/crc.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>

void SteamClient::HandleEncryptionHandshake(MsgHdr &h, TcpPacket &p) {
    using namespace CryptoPP;

    switch ((EMsg)h.msg) {
    case EMsg::ChannelEncryptRequest: {
        MsgChannelEncryptRequest r;
        r.FromBuffer(p.body);
        printf("proto: %d, universe: %d\n", r.protocolVersion, r.universe);

        CryptoPP::RSA::PublicKey publicKey;

        ArraySource source(PUBLIC_KEY, sizeof(PUBLIC_KEY), true);
        publicKey.Load(source);

        RSAES_OAEP_SHA_Encryptor rsa(publicKey);
        auto                     rsaSize = rsa.FixedCiphertextLength();

        AutoSeededRandomPool rnd;
        rnd.GenerateBlock(sessionKey, sizeof(sessionKey));

        MsgBuilder w{EMsg::ChannelEncryptResponse};

        auto &b = w.GetBody();
        b.Write(MsgChannelEncryptResponse{}.ToBuffer());

        u8 cryptedSessionKey[128];

        rsa.Encrypt(rnd, sessionKey, sizeof(sessionKey), cryptedSessionKey);
        b.Write(cryptedSessionKey);

        u8 crc[4];

        CRC32().CalculateDigest(crc, cryptedSessionKey, rsaSize);
        b.Write(crc);
        b.Write(0);

        WriteMessage(w);
    } break;
    case EMsg::ChannelEncryptResult: {
        MsgChannelEncryptResult r;
        r.FromBuffer(p.body);
        printf("result: %d\n", r.result);
    }
    default: {
    }
    }
}

bool SteamClient::ProcessPacket(TcpPacket &p) {
    printf("Processing packet...\n");

    p.body.SetPos(0);
    auto fullMessage = p.body.Read<u32>();

    auto isProto    = IsProto(fullMessage);
    auto rawMessage = RawMsg(fullMessage);

    printf("Message: %d\n", rawMessage);

    if (!isProto) {
        switch (rawMessage) {
        case EMsg::ChannelEncryptRequest:
        case EMsg::ChannelEncryptResult: {
            printf("Encryption handshake\n");
            p.body.SetPos(0);

            auto hdr = MsgHdr{};
            hdr.FromBuffer(p.body);
            HandleEncryptionHandshake(hdr, p);
        } break;

        default: {
            printf("Default... %d\n", rawMessage);
        } break;
        }
    } else {
        printf("Proto message %d\n", rawMessage);
    }

    return false;
}

void SteamClient::WriteMessage(MsgBuilder &b) {
    auto &body = b.Finish();

    if (!encrypted) {
    } else {
    }

    printf("Final message size is %d\n", body.Size());

    s.Write(body.Storage());
}
