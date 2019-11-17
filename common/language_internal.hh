#pragma once

#include "emsg.hh"
#include "language.hh"

#include "platform.hh"

#pragma pack(push, 1)

class Buffer;

namespace Argonx {
struct UdpHeader {
    static const u32 MAGIC = 0x31305356;
    // Static size: 4
    u32 magic;
    // Static size: 2
    u16 payloadSize;
    // Static size: 1
    u8 packetType;
    // Static size: 1
    u8 flags;
    // Static size: 4
    u32 sourceConnID;
    // Static size: 4
    u32 destConnID;
    // Static size: 4
    u32 seqThis;
    // Static size: 4
    u32 seqAck;
    // Static size: 4
    u32 packetsInMsg;
    // Static size: 4
    u32 msgStartSeq;
    // Static size: 4
    u32 msgSize;

    UdpHeader() {
        magic        = UdpHeader::MAGIC;
        payloadSize  = 0;
        packetType   = static_cast<u8>(EUdpPacketType::Invalid);
        flags        = 0;
        sourceConnID = 512;
        destConnID   = 0;
        seqThis      = 0;
        seqAck       = 0;
        packetsInMsg = 0;
        msgStartSeq  = 0;
        msgSize      = 0;
    }
};

struct ChallengeData {
    static const u32 CHALLENGE_MASK = 0xA426DF2B;
    // Static size: 4
    u32 challengeValue;
    // Static size: 4
    u32 serverLoad;

    ChallengeData() {
        challengeValue = 0;
        serverLoad     = 0;
    }
};

struct ConnectData {
    static const u32 CHALLENGE_MASK = ChallengeData::CHALLENGE_MASK;
    // Static size: 4
    u32 challengeValue;

    ConnectData() {
        challengeValue = 0;
    }
};

struct Accept {

    Accept() {
    }
};

struct Datagram {

    Datagram() {
    }
};

struct Disconnect {

    Disconnect() {
    }
};

struct MsgHdr {
    // Static size: 4
    u32 msg;
    // Static size: 8
    u64 targetJobID;
    // Static size: 8
    u64 sourceJobID;

    MsgHdr() {
        msg         = static_cast<u32>(EMsg::Invalid);
        targetJobID = UINT64_MAX;
        sourceJobID = UINT64_MAX;
    }

    void   FromBuffer(Buffer &b);
    Buffer ToBuffer();
};

struct ExtendedClientMsgHdr {
    // Static size: 4
    u32 msg;
    // Static size: 1
    u8 headerSize;
    // Static size: 2
    u16 headerVersion;
    // Static size: 8
    u64 targetJobID;
    // Static size: 8
    u64 sourceJobID;
    // Static size: 1
    u8 headerCanary;
    // Static size: 8
    u64 steamID;
    // Static size: 4
    i32 sessionID;

    ExtendedClientMsgHdr() {
        msg           = static_cast<u32>(EMsg::Invalid);
        headerSize    = 36;
        headerVersion = 2;
        targetJobID   = UINT64_MAX;
        sourceJobID   = UINT64_MAX;
        headerCanary  = 239;
        steamID       = 0;
        sessionID     = 0;
    }

    void FromBuffer(Buffer &b);
};

struct MsgHdrProtoBuf {
    // Static size: 4
    u32 msg;
    // Static size: 4
    i32 headerLength;
    // Static size: 0
    // unsigned char proto[0];

    MsgHdrProtoBuf() {
        msg          = static_cast<u32>(EMsg::Invalid);
        headerLength = 0;
    }

    void   FromBuffer(Buffer &b);
    Buffer ToBuffer();
};

struct MsgGCHdrProtoBuf {
    // Static size: 4
    u32 msg;
    // Static size: 4
    i32 headerLength;
    // Static size: 0
    // unsigned char proto[0];

    MsgGCHdrProtoBuf() {
        msg          = 0;
        headerLength = 0;
    }
};

struct MsgGCHdr {
    // Static size: 2
    u16 headerVersion;
    // Static size: 8
    u64 targetJobID;
    // Static size: 8
    u64 sourceJobID;

    MsgGCHdr() {
        headerVersion = 1;
        targetJobID   = UINT64_MAX;
        sourceJobID   = UINT64_MAX;
    }
};

struct MsgClientJustStrings {

    MsgClientJustStrings() {
    }
};

struct MsgClientGenericResponse {
    // Static size: 4
    u32 result;

    MsgClientGenericResponse() {
        result = 0;
    }
};

struct MsgChannelEncryptRequest {
    static const u32 PROTOCOL_VERSION = 1;
    // Static size: 4
    u32 protocolVersion;
    // Static size: 4
    u32 universe;

    MsgChannelEncryptRequest() {
        protocolVersion = MsgChannelEncryptRequest::PROTOCOL_VERSION;
        universe        = static_cast<u32>(EUniverse::Invalid);
    }

    void FromBuffer(Buffer &b);
};

struct MsgChannelEncryptResponse {
    // Static size: 4
    u32 protocolVersion;
    // Static size: 4
    u32 keySize;

    MsgChannelEncryptResponse() {
        protocolVersion = MsgChannelEncryptRequest::PROTOCOL_VERSION;
        keySize         = 128;
    }

    Buffer ToBuffer();
};

struct MsgChannelEncryptResult {
    // Static size: 4
    u32 result;

    MsgChannelEncryptResult() {
        result = static_cast<u32>(EResult::Invalid);
    }

    void FromBuffer(Buffer &b);
};

struct MsgClientNewLoginKey {
    // Static size: 4
    u32 uniqueID;
    // Static size: 20
    unsigned char loginKey[20];

    MsgClientNewLoginKey() {
        uniqueID = 0;
    }
};

struct MsgClientNewLoginKeyAccepted {
    // Static size: 4
    u32 uniqueID;

    MsgClientNewLoginKeyAccepted() {
        uniqueID = 0;
    }
};

struct MsgClientLogon {
    static const u32 ObfuscationMask                                      = 0xBAADF00D;
    static const u32 CurrentProtocol                                      = 65575;
    static const u32 ProtocolVerMajorMask                                 = 0xFFFF0000;
    static const u32 ProtocolVerMinorMask                                 = 0xFFFF;
    static const u16 ProtocolVerMinorMinGameServers                       = 4;
    static const u16 ProtocolVerMinorMinForSupportingEMsgMulti            = 12;
    static const u16 ProtocolVerMinorMinForSupportingEMsgClientEncryptPct = 14;
    static const u16 ProtocolVerMinorMinForExtendedMsgHdr                 = 17;
    static const u16 ProtocolVerMinorMinForCellId                         = 18;
    static const u16 ProtocolVerMinorMinForSessionIDLast                  = 19;
    static const u16 ProtocolVerMinorMinForServerAvailablityMsgs          = 24;
    static const u16 ProtocolVerMinorMinClients                           = 25;
    static const u16 ProtocolVerMinorMinForOSType                         = 26;
    static const u16 ProtocolVerMinorMinForCegApplyPESig                  = 27;
    static const u16 ProtocolVerMinorMinForMarketingMessages2             = 27;
    static const u16 ProtocolVerMinorMinForAnyProtoBufMessages            = 28;
    static const u16 ProtocolVerMinorMinForProtoBufLoggedOffMessage       = 28;
    static const u16 ProtocolVerMinorMinForProtoBufMultiMessages          = 28;
    static const u16 ProtocolVerMinorMinForSendingProtocolToUFS           = 30;
    static const u16 ProtocolVerMinorMinForMachineAuth                    = 33;

    MsgClientLogon() {
    }
};

struct MsgClientVACBanStatus {
    // Static size: 4
    u32 numBans;

    MsgClientVACBanStatus() {
        numBans = 0;
    }
};

struct MsgClientAppUsageEvent {
    // Static size: 4
    u32 appUsageEvent;
    // Static size: 8
    u64 gameID;
    // Static size: 2
    u16 offline;

    MsgClientAppUsageEvent() {
        appUsageEvent = 0;
        gameID        = 0;
        offline       = 0;
    }
};

struct MsgClientEmailAddrInfo {
    // Static size: 4
    u32 passwordStrength;
    // Static size: 4
    u32 flagsAccountSecurityPolicy;
    // Static size: 1
    u8 validated;

    MsgClientEmailAddrInfo() {
        passwordStrength           = 0;
        flagsAccountSecurityPolicy = 0;
        validated                  = 0;
    }
};

struct MsgClientUpdateGuestPassesList {
    // Static size: 4
    u32 result;
    // Static size: 4
    i32 countGuestPassesToGive;
    // Static size: 4
    i32 countGuestPassesToRedeem;

    MsgClientUpdateGuestPassesList() {
        result                   = 0;
        countGuestPassesToGive   = 0;
        countGuestPassesToRedeem = 0;
    }
};

struct MsgClientRequestedClientStats {
    // Static size: 4
    i32 countStats;

    MsgClientRequestedClientStats() {
        countStats = 0;
    }
};

struct MsgClientP2PIntroducerMessage {
    // Static size: 8
    u64 steamID;
    // Static size: 4
    u32 routingType;
    // Static size: 1450
    unsigned char data[1450];
    // Static size: 4
    u32 dataLen;

    MsgClientP2PIntroducerMessage() {
        steamID     = 0;
        routingType = 0;
        dataLen     = 0;
    }
};

struct MsgClientOGSBeginSession {
    // Static size: 1
    u8 accountType;
    // Static size: 8
    u64 accountId;
    // Static size: 4
    u32 appId;
    // Static size: 4
    u32 timeStarted;

    MsgClientOGSBeginSession() {
        accountType = 0;
        accountId   = 0;
        appId       = 0;
        timeStarted = 0;
    }
};

struct MsgClientOGSBeginSessionResponse {
    // Static size: 4
    u32 result;
    // Static size: 1
    u8 collectingAny;
    // Static size: 1
    u8 collectingDetails;
    // Static size: 8
    u64 sessionId;

    MsgClientOGSBeginSessionResponse() {
        result            = 0;
        collectingAny     = 0;
        collectingDetails = 0;
        sessionId         = 0;
    }
};

struct MsgClientOGSEndSession {
    // Static size: 8
    u64 sessionId;
    // Static size: 4
    u32 timeEnded;
    // Static size: 4
    i32 reasonCode;
    // Static size: 4
    i32 countAttributes;

    MsgClientOGSEndSession() {
        sessionId       = 0;
        timeEnded       = 0;
        reasonCode      = 0;
        countAttributes = 0;
    }
};

struct MsgClientOGSEndSessionResponse {
    // Static size: 4
    u32 result;

    MsgClientOGSEndSessionResponse() {
        result = 0;
    }
};

struct MsgClientOGSWriteRow {
    // Static size: 8
    u64 sessionId;
    // Static size: 4
    i32 countAttributes;

    MsgClientOGSWriteRow() {
        sessionId       = 0;
        countAttributes = 0;
    }
};

struct MsgClientGetFriendsWhoPlayGame {
    // Static size: 8
    u64 gameId;

    MsgClientGetFriendsWhoPlayGame() {
        gameId = 0;
    }
};

struct MsgClientGetFriendsWhoPlayGameResponse {
    // Static size: 4
    u32 result;
    // Static size: 8
    u64 gameId;
    // Static size: 4
    u32 countFriends;

    MsgClientGetFriendsWhoPlayGameResponse() {
        result       = 0;
        gameId       = 0;
        countFriends = 0;
    }
};

struct MsgGSPerformHardwareSurvey {
    // Static size: 4
    u32 flags;

    MsgGSPerformHardwareSurvey() {
        flags = 0;
    }
};

struct MsgGSGetPlayStatsResponse {
    // Static size: 4
    u32 result;
    // Static size: 4
    i32 rank;
    // Static size: 4
    u32 lifetimeConnects;
    // Static size: 4
    u32 lifetimeMinutesPlayed;

    MsgGSGetPlayStatsResponse() {
        result                = 0;
        rank                  = 0;
        lifetimeConnects      = 0;
        lifetimeMinutesPlayed = 0;
    }
};

struct MsgGSGetReputationResponse {
    // Static size: 4
    u32 result;
    // Static size: 4
    u32 reputationScore;
    // Static size: 1
    u8 banned;
    // Static size: 4
    u32 bannedIp;
    // Static size: 2
    u16 bannedPort;
    // Static size: 8
    u64 bannedGameId;
    // Static size: 4
    u32 timeBanExpires;

    MsgGSGetReputationResponse() {
        result          = 0;
        reputationScore = 0;
        banned          = 0;
        bannedIp        = 0;
        bannedPort      = 0;
        bannedGameId    = 0;
        timeBanExpires  = 0;
    }
};

struct MsgGSDeny {
    // Static size: 8
    u64 steamId;
    // Static size: 4
    u32 denyReason;

    MsgGSDeny() {
        steamId    = 0;
        denyReason = 0;
    }
};

struct MsgGSApprove {
    // Static size: 8
    u64 steamId;

    MsgGSApprove() {
        steamId = 0;
    }
};

struct MsgGSKick {
    // Static size: 8
    u64 steamId;
    // Static size: 4
    u32 denyReason;
    // Static size: 4
    i32 waitTilMapChange;

    MsgGSKick() {
        steamId          = 0;
        denyReason       = 0;
        waitTilMapChange = 0;
    }
};

struct MsgGSGetUserGroupStatus {
    // Static size: 8
    u64 steamIdUser;
    // Static size: 8
    u64 steamIdGroup;

    MsgGSGetUserGroupStatus() {
        steamIdUser  = 0;
        steamIdGroup = 0;
    }
};

struct MsgGSGetUserGroupStatusResponse {
    // Static size: 8
    u64 steamIdUser;
    // Static size: 8
    u64 steamIdGroup;
    // Static size: 4
    u32 clanRelationship;
    // Static size: 4
    u32 clanRank;

    MsgGSGetUserGroupStatusResponse() {
        steamIdUser      = 0;
        steamIdGroup     = 0;
        clanRelationship = 0;
        clanRank         = 0;
    }
};

struct MsgClientJoinChat {
    // Static size: 8
    u64 steamIdChat;
    // Static size: 1
    u8 isVoiceSpeaker;

    MsgClientJoinChat() {
        steamIdChat    = 0;
        isVoiceSpeaker = 0;
    }
};

struct MsgClientChatEnter {
    // Static size: 8
    u64 steamIdChat;
    // Static size: 8
    u64 steamIdFriend;
    // Static size: 4
    u32 chatRoomType;
    // Static size: 8
    u64 steamIdOwner;
    // Static size: 8
    u64 steamIdClan;
    // Static size: 1
    u8 chatFlags;
    // Static size: 4
    u32 enterResponse;

    MsgClientChatEnter() {
        steamIdChat   = 0;
        steamIdFriend = 0;
        chatRoomType  = 0;
        steamIdOwner  = 0;
        steamIdClan   = 0;
        chatFlags     = 0;
        enterResponse = 0;
    }
};

struct MsgClientChatMsg {
    // Static size: 8
    u64 steamIdChatter;
    // Static size: 8
    u64 steamIdChatRoom;
    // Static size: 4
    u32 chatMsgType;

    MsgClientChatMsg() {
        steamIdChatter  = 0;
        steamIdChatRoom = 0;
        chatMsgType     = 0;
    }
};

struct MsgClientChatMemberInfo {
    // Static size: 8
    u64 steamIdChat;
    // Static size: 4
    u32 type;

    MsgClientChatMemberInfo() {
        steamIdChat = 0;
        type        = 0;
    }
};

struct MsgClientChatAction {
    // Static size: 8
    u64 steamIdChat;
    // Static size: 8
    u64 steamIdUserToActOn;
    // Static size: 4
    u32 chatAction;

    MsgClientChatAction() {
        steamIdChat        = 0;
        steamIdUserToActOn = 0;
        chatAction         = 0;
    }
};

struct MsgClientChatActionResult {
    // Static size: 8
    u64 steamIdChat;
    // Static size: 8
    u64 steamIdUserActedOn;
    // Static size: 4
    u32 chatAction;
    // Static size: 4
    u32 actionResult;

    MsgClientChatActionResult() {
        steamIdChat        = 0;
        steamIdUserActedOn = 0;
        chatAction         = 0;
        actionResult       = 0;
    }
};

struct MsgClientGetNumberOfCurrentPlayers {
    // Static size: 8
    u64 gameID;

    MsgClientGetNumberOfCurrentPlayers() {
        gameID = 0;
    }
};

struct MsgClientGetNumberOfCurrentPlayersResponse {
    // Static size: 4
    u32 result;
    // Static size: 4
    u32 numPlayers;

    MsgClientGetNumberOfCurrentPlayersResponse() {
        result     = 0;
        numPlayers = 0;
    }
};

struct MsgClientSetIgnoreFriend {
    // Static size: 8
    u64 mySteamId;
    // Static size: 8
    u64 steamIdFriend;
    // Static size: 1
    u8 ignore;

    MsgClientSetIgnoreFriend() {
        mySteamId     = 0;
        steamIdFriend = 0;
        ignore        = 0;
    }
};

struct MsgClientSetIgnoreFriendResponse {
    // Static size: 8
    u64 unknown;
    // Static size: 4
    u32 result;

    MsgClientSetIgnoreFriendResponse() {
        unknown = 0;
        result  = 0;
    }
};

struct MsgClientLoggedOff {
    // Static size: 4
    u32 result;
    // Static size: 4
    i32 secMinReconnectHint;
    // Static size: 4
    i32 secMaxReconnectHint;

    MsgClientLoggedOff() {
        result              = 0;
        secMinReconnectHint = 0;
        secMaxReconnectHint = 0;
    }
};

struct MsgClientLogOnResponse {
    // Static size: 4
    u32 result;
    // Static size: 4
    i32 outOfGameHeartbeatRateSec;
    // Static size: 4
    i32 inGameHeartbeatRateSec;
    // Static size: 8
    u64 clientSuppliedSteamId;
    // Static size: 4
    u32 ipPublic;
    // Static size: 4
    u32 serverRealTime;

    MsgClientLogOnResponse() {
        result                    = 0;
        outOfGameHeartbeatRateSec = 0;
        inGameHeartbeatRateSec    = 0;
        clientSuppliedSteamId     = 0;
        ipPublic                  = 0;
        serverRealTime            = 0;
    }
};

struct MsgClientSendGuestPass {
    // Static size: 8
    u64 giftId;
    // Static size: 1
    u8 giftType;
    // Static size: 4
    u32 accountId;

    MsgClientSendGuestPass() {
        giftId    = 0;
        giftType  = 0;
        accountId = 0;
    }
};

struct MsgClientSendGuestPassResponse {
    // Static size: 4
    u32 result;

    MsgClientSendGuestPassResponse() {
        result = 0;
    }
};

struct MsgClientServerUnavailable {
    // Static size: 8
    u64 jobidSent;
    // Static size: 4
    u32 eMsgSent;
    // Static size: 4
    u32 eServerTypeUnavailable;

    MsgClientServerUnavailable() {
        jobidSent              = 0;
        eMsgSent               = 0;
        eServerTypeUnavailable = 0;
    }
};

struct MsgClientMarketingMessageUpdate2 {
    u32 marketingMessageUpdateTime;
    u32 count;

    void FromBuffer(Buffer &b);
};

} // namespace Argonx

#pragma pack(pop)
