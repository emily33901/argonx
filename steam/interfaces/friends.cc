#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientFriends.h"
#include "SteamStructs/IClientUser.h"
} // namespace Reference

#include "argonx/cmclient/cmclient.hh"
#include "argonx/cmclient/steamcrypt.hh"
#include "argonx/cmclient/steamhandlers.hh"

#include "steammessages_clientserver.pb.h"
#include "steammessages_clientserver_2.pb.h"
#include "steammessages_clientserver_friends.pb.h"

struct SteamEntity {
    Argonx::SteamId id;
    union {
        Steam::EFriendRelationship friendRelationship;
        Steam::EClanRelationship   clanRelationship;
    };

    SteamEntity(Argonx::SteamId id, Steam::EFriendRelationship relation) : id(id), friendRelationship(relation) {
    }

    SteamEntity(Argonx::SteamId id, Steam::EClanRelationship relation) : id(id), clanRelationship(relation) {
    }

    bool IsFriend() {
        return Steam::CSteamID(id).BIndividualAccount();
    }

    bool IsClan() {
        return Steam::CSteamID(id).BClanAccount();
    }
};

template <bool isServer>
class ClientFriendsMap : public Reference::IClientFriends {
    UserHandle userHandle;

public:
    std::vector<SteamEntity> friends;
    std::vector<SteamEntity> clans;

    static void OnClientFriendsList(Argonx::CMClient *c, u32 msgSize, Buffer &b, u64 jobId) {
        auto self = LookupInterface<ClientFriendsMap<false>>(c, Steam::InterfaceTarget::friends);

        auto msg = b.ReadAsProto<CMsgClientFriendsList>(msgSize);

        if (!msg.bincremental()) {
            self->friends.clear();
        }

        using IterType = std::vector<SteamEntity>::iterator;
        std::vector<IterType> friendsToRemove;
        std::vector<IterType> clansToRemove;

        for (const auto &f : msg.friends()) {
            auto steamId = Argonx::SteamId(f.ulfriendid());

            if (Steam::CSteamID(f.ulfriendid()).BClanAccount()) {
                auto relation = (Steam::EClanRelationship)f.efriendrelationship();

                auto iter = std::find_if(self->clans.begin(), self->clans.end(), [steamId](const auto &x) -> bool { return x.id == steamId; });
                if (iter != self->clans.end()) {
                    // If we already have this account then its probably being removed
                    // but make sure anyway...
                    if (relation == Steam::EClanRelationship::eClanRelationshipNone || relation == Steam::EClanRelationship::eClanRelationshipKicked) {
                        clansToRemove.push_back(iter);
                    } else {
                        self->clans.push_back(SteamEntity(steamId, relation));
                    }
                }
            } else if (Steam::CSteamID(f.ulfriendid()).BIndividualAccount()) {
                auto relation = (Steam::EFriendRelationship)f.efriendrelationship();

                auto iter = std::find_if(self->friends.begin(), self->friends.end(), [steamId](const auto &x) -> bool { return x.id == steamId; });

                if (iter != self->friends.end()) {
                    // If we already have this account then its probably being removed
                    // but make sure anyway...
                    if (relation == Steam::EFriendRelationship::k_EFriendRelationshipNone) {
                        friendsToRemove.push_back(iter);
                    } else {
                        self->friends.push_back(SteamEntity(steamId, relation));
                    }
                }
            }
            // Check relationships to see whether we need to remove or add friends

            // Also check for clan accounts and add them seperately
            // friends.push_back({Argonx::SteamId(f.ulfriendid()),
            //                    (Steam::EFriendRelationship)f.efriendrelationship()});
        }

        LOG_F(INFO, "Got %d friends and %d clans", self->friends.size(), self->clans.size());
    }

    std::string personaName;
    EPersonaState personaState;

public:
    ClientFriendsMap(UserHandle h) : userHandle(h) {
        RpcRunOnServer() {
            personaState = EPersonaState::k_EPersonaStateOffline;
        }
    }
    // Inherited via IClientFriends
    virtual const char *GetPersonaName() override {
        RpcMakeCallIfClient(GetPersonaName, friends, ) {
            return personaName.c_str();
        }
    }
    virtual SteamAPICall_t SetPersonaName(char const *newName) override {
        return SetPersonaNameEx(newName, true);
    }
    virtual SteamAPICall_t SetPersonaNameEx(char const *newName, bool sendCallback) override {
        RpcMakeCallIfClient(SetPersonaNameEx, friends, newName, sendCallback) {
            auto job = Steam::NewAsyncJob([this](const Steam::AsyncJob &b) -> Steam::AsyncJob::Result {
                // Check if we got a namechange callback
                // If we did return finished

                return Steam::AsyncJob::Result::yield;
            });

            return job.jobId;
        }
    }
    virtual bool IsPersonaNameSet() override {
        RpcMakeCallIfClient(IsPersonaNameSet, friends,) {
            return personaName != "";
        }
    }
    virtual EPersonaState GetPersonaState() override {
        RpcMakeCallIfClient(GetPersonaState, friends, ) {
            return personaState;
        }
    }
    virtual void SetPersonaState(EPersonaState state) override {
        RpcMakeCallIfClient(SetPersonaState, friends, state) {
            personaState = state;
        }
    }
    virtual unknown_ret NotifyUIOfMenuChange(bool showAvatar, bool sortByName, bool showOnlineOnly, bool showUntaggedFriends) override {
        // I assume that this refers to the friends menu - is this even used now that we have the new friends UI?
        return unknown_ret();
    }
    virtual int GetFriendCount(EFriendFlags friendFlags) override {
        RpcMakeCallIfClient(GetFriendCount, friends, friendFlags) {
            auto *user = LookupInterface<Reference::IClientUser>(userHandle, InterfaceTarget::user);

            auto count = 0;
            
            for (auto &f : friends) {
                if ((f.friendRelationship & friendFlags) == friendFlags) {
                    count += 1;
                }
            }

            return count;
        }

    }
    virtual unknown_ret GetFriendArray(CSteamID *, signed char *, int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendArrayInGame(CSteamID *, unsigned long long *, int) override {
        return unknown_ret();
    }
    virtual CSteamID GetFriendByIndex(int index, EFriendFlags flags) override {
        RpcMakeCallIfClient(GetFriendByIndex, friends, index, flags) {
            auto count = 0;
            for (const auto it = friends.begin(); f != friends.end(); f++) {
                if ((it->friendRelationship & flags) == flags) {
                    count += 1;
                }
            }
        }
    }
    virtual unknown_ret GetOnlineFriendCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendRelationship(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendPersonaState(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendPersonaName(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSmallFriendAvatar(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMediumFriendAvatar(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLargeFriendAvatar(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetFriendAvatarURL(char *, unsigned int, CSteamID, EFriendAvatarSize) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendAvatarHash(char *, unsigned int, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetFriendRegValue(CSteamID, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendRegValue(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret DeleteFriendRegValue(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendGamePlayed(CSteamID, FriendGameInfo_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendGamePlayedExtraInfo(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendGameServer(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendPersonaStateFlags(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret IsFriendGameOnConsole(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendSessionStateInfo(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendRestrictions(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendBroadcastID(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendPersonaNameHistory(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestPersonaNameHistory(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendPersonaNameHistoryAndDate(CSteamID, int, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret AddFriend(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveFriend(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret HasFriend(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestUserInformation(CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetIgnoreFriend(CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret ReportChatDeclined(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateFriendsGroup(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret DeleteFriendsGroup(short) override {
        return unknown_ret();
    }
    virtual unknown_ret RenameFriendsGroup(char const *, short) override {
        return unknown_ret();
    }
    virtual unknown_ret AddFriendToGroup(CSteamID, short) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveFriendFromGroup(CSteamID, short) override {
        return unknown_ret();
    }
    virtual unknown_ret IsFriendMemberOfFriendsGroup(CSteamID, short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendsGroupCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendsGroupIDByIndex(short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendsGroupName(short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendsGroupMembershipCount(short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFirstFriendsGroupMember(short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNextFriendsGroupMember(short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGroupFriendsMembershipCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFirstGroupFriendsMember(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNextGroupFriendsMember(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetPlayerNickname(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetPlayerNickname(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendSteamLevel(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatMessagesCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatMessage(CSteamID, int, void *, int, EChatEntryType *, unsigned long long *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SendMsgToFriend(CSteamID, EChatEntryType, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearChatHistory(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetKnownClanCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetKnownClanByIndex(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanByIndex(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanName(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanTag(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendActivityCounts(int *, int *, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanActivityCounts(CSteamID, int *, int *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret DownloadClanActivityCounts(CSteamID *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendsGroupActivityCounts(short, int *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret IsClanPublic(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret IsClanOfficialGameGroup(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret JoinClanChatRoom(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret LeaveClanChatRoom(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanChatMemberCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatMemberByIndex(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SendClanChatMessage(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanChatMessage(CSteamID, int, void *, int, EChatEntryType *, CSteamID *) override {
        return unknown_ret();
    }
    virtual unknown_ret IsClanChatAdmin(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret IsClanChatWindowOpenInSteam(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret OpenClanChatWindowInSteam(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret CloseClanChatWindowInSteam(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetListenForFriendsMessages(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret ReplyToFriendMessage(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendMessage(CSteamID, int, void *, int, EChatEntryType *) override {
        return unknown_ret();
    }
    virtual unknown_ret InviteFriendToClan(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret AcknowledgeInviteToClan(CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendCountFromSource(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendFromSourceByIndex(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsUserInSource(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCoplayFriendCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetCoplayFriend(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendCoplayTime(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendCoplayGame(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetRichPresence(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearRichPresence(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendRichPresence(unsigned int, CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendRichPresenceKeyCount(unsigned int, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendRichPresenceKeyByIndex(unsigned int, CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestFriendRichPresence(unsigned int, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret JoinChatRoom(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret LeaveChatRoom(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret InviteUserToChatRoom(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SendChatMsg(CSteamID, EChatEntryType, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomMessagesCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomEntry(CSteamID, int, CSteamID *, void *, int, EChatEntryType *) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearChatRoomHistory(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SerializeChatRoomDlg(CSteamID, void const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSizeOfSerializedChatRoomDlg(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSerializedChatRoomDlg(CSteamID, void *, int, int *, EChatRoomType *) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearSerializedChatRoomDlg(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret KickChatMember(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret BanChatMember(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret UnBanChatMember(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetChatRoomType(CSteamID, ELobbyType) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomLockState(CSteamID, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomPermissions(CSteamID, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetChatRoomModerated(CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret BChatRoomModerated(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret NotifyChatRoomDlgsOfUIChange(CSteamID, bool, bool, bool, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret TerminateChatRoom(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomByIndex(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomName(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetChatRoomMemberDetails(CSteamID, CSteamID, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateChatRoom(EChatRoomType, unsigned long long, char const *, ELobbyType, CSteamID, CSteamID, CSteamID, unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret JoinChatRoomGroup(unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret ShowChatRoomGroupInvite(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret VoiceCallNew(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret VoiceCall(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret VoiceHangUp(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetVoiceSpeakerVolume(float) override {
        return unknown_ret();
    }
    virtual unknown_ret SetVoiceMicrophoneVolume(float) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAutoAnswer(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret VoiceAnswer(int) override {
        return unknown_ret();
    }
    virtual unknown_ret AcceptVoiceCall(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret VoicePutOnHold(int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret BVoiceIsLocalOnHold(int) override {
        return unknown_ret();
    }
    virtual unknown_ret BVoiceIsRemoteOnHold(int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDoNotDisturb(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret EnableVoiceNotificationSounds(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetPushToTalkEnabled(bool, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IsPushToTalkEnabled() override {
        return unknown_ret();
    }
    virtual unknown_ret IsPushToMuteEnabled() override {
        return unknown_ret();
    }
    virtual unknown_ret SetPushToTalkKey(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetPushToTalkKey() override {
        return unknown_ret();
    }
    virtual unknown_ret IsPushToTalkKeyDown() override {
        return unknown_ret();
    }
    virtual unknown_ret EnableVoiceCalibration(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IsVoiceCalibrating() override {
        return unknown_ret();
    }
    virtual unknown_ret GetVoiceCalibrationSamplePeak() override {
        return unknown_ret();
    }
    virtual unknown_ret SetMicBoost(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMicBoost() override {
        return unknown_ret();
    }
    virtual unknown_ret HasHardwareMicBoost() override {
        return unknown_ret();
    }
    virtual unknown_ret GetMicDeviceName() override {
        return unknown_ret();
    }
    virtual unknown_ret StartTalking(int) override {
        return unknown_ret();
    }
    virtual unknown_ret EndTalking(int) override {
        return unknown_ret();
    }
    virtual unknown_ret VoiceIsValid(int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAutoReflectVoice(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCallState(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetVoiceMicrophoneVolume() override {
        return unknown_ret();
    }
    virtual unknown_ret GetVoiceSpeakerVolume() override {
        return unknown_ret();
    }
    virtual unknown_ret TimeSinceLastVoiceDataReceived(int) override {
        return unknown_ret();
    }
    virtual unknown_ret TimeSinceLastVoiceDataSend(int) override {
        return unknown_ret();
    }
    virtual unknown_ret BCanSend(int) override {
        return unknown_ret();
    }
    virtual unknown_ret BCanReceive(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetEstimatedBitsPerSecond(int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetPeakSample(int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SendResumeRequest(int) override {
        return unknown_ret();
    }
    virtual unknown_ret OpenFriendsDialog(bool, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret OpenChatDialog(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret OpenInviteToTradeDialog(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret StartChatRoomVoiceSpeaking(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret EndChatRoomVoiceSpeaking(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendLastLogonTime(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendLastLogoffTime(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomVoiceTotalSlotCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomVoiceUsedSlotCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomVoiceUsedSlot(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomVoiceStatus(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret BChatRoomHasAvailableVoiceSlots(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsChatRoomVoiceSpeaking(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetChatRoomPeakSample(CSteamID, CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret ChatRoomVoiceRetryConnections(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetPortTypes(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ReinitAudio() override {
        return unknown_ret();
    }
    virtual unknown_ret SetInGameVoiceSpeaking(CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IsInGameVoiceSpeaking() override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateGameOverlay(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateGameOverlayToUser(char const *, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateGameOverlayToWebPage(char const *, EActivateGameOverlayToWebPageMode) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateGameOverlayToStore(unsigned int, EOverlayToStoreFlag) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateGameOverlayInviteDialog(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret ProcessActivateGameOverlayInMainUI(char const *, CSteamID, unsigned int, bool, int) override {
        return unknown_ret();
    }
    virtual unknown_ret NotifyGameOverlayStateChanged(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret NotifyGameServerChangeRequested(char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret NotifyLobbyJoinRequested(unsigned int, CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret NotifyRichPresenceJoinRequested(unsigned int, CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanRelationship(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanInviteCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendClanRank(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret VoiceIsAvailable() override {
        return unknown_ret();
    }
    virtual unknown_ret TestVoiceDisconnect(int) override {
        return unknown_ret();
    }
    virtual unknown_ret TestChatRoomPeerDisconnect(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret TestVoicePacketLoss(float) override {
        return unknown_ret();
    }
    virtual unknown_ret FindFriendVoiceChatHandle(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestFriendsWhoPlayGame(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCountFriendsWhoPlayGame(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendWhoPlaysGame(unsigned int, CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCountFriendsInGame(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetPlayedWith(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestClanOfficerList(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanOwner(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanOfficerCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetClanOfficerByIndex(CSteamID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserRestrictions() override {
        return unknown_ret();
    }
    virtual unknown_ret RequestFriendProfileInfo(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendProfileInfo(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret InviteUserToGame(unsigned int, CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetOnlineConsoleFriendCount() override {
        return unknown_ret();
    }
    virtual unknown_ret RequestTrade(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret TradeResponse(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret CancelTradeRequest(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret HideFriend(CSteamID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFollowerCount(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret IsFollowing(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateFollowingList(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestFriendMessageHistory(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestFriendMessageHistoryForOfflineMessages() override {
        return unknown_ret();
    }
    virtual unknown_ret GetCountFriendsWithOfflineMessages() override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendWithOfflineMessage(int) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearFriendHasOfflineMessage(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestEmoticonList() override {
        return unknown_ret();
    }
    virtual unknown_ret GetEmoticonCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetEmoticonName(int) override {
        return unknown_ret();
    }
    virtual unknown_ret ClientLinkFilterInit() override {
        return unknown_ret();
    }
    virtual unknown_ret LinkDisposition(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFriendPersonaName_Public(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetPlayerNickname_Public(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret SetFriendsUIActiveClanChatList(unsigned int *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumChatsWithUnreadPriorityMessages() override {
        return unknown_ret();
    }
    virtual unknown_ret SetNumChatsWithUnreadPriorityMessages(int) override {
        return unknown_ret();
    }
};

RegisterHelperUnique(Argonx::EMsg::ClientFriendsList, ClientFriendsMap<true>::OnClientFriendsList);

AdaptExposeClientServer(ClientFriendsMap, "SteamFriends");

using IClientFriendsMap = ClientFriendsMap<false>;

AdaptDeclare(ISteamFriends002);
AdaptDefine(ISteamFriends002, IClientFriendsMap, "SteamFriends002") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::SetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetFriendRegValue),
    AdaptPassThrough(IClientFriendsMap::GetFriendRegValue),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::AddFriend),
    AdaptPassThrough(IClientFriendsMap::RemoveFriend),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptEmpty(IClientFriendsMap::AddFriendByName),
    AdaptEmpty(IClientFriendsMap::InviteFriendByEmail),
    AdaptPassThrough(IClientFriendsMap::GetChatMessage),
    AdaptPassThrough(IClientFriendsMap::SendMsgToFriend),
    AdaptEmpty(IClientFriendsMap::GetChatIDOfChatHistoryStart),
    AdaptEmpty(IClientFriendsMap::SetChatHistoryStart),
    AdaptPassThrough(IClientFriendsMap::ClearChatHistory),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::InviteFriendToClan),
    AdaptPassThrough(IClientFriendsMap::AcknowledgeInviteToClan),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
};
AdaptDeclare(ISteamFriends003);
AdaptDefine(ISteamFriends003, IClientFriendsMap, "SteamFriends003") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptEmpty(IClientFriendsMap::GetFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
};
AdaptDeclare(ISteamFriends004);
AdaptDefine(ISteamFriends004, IClientFriendsMap, "SteamFriends004") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptEmpty(IClientFriendsMap::GetFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
};
AdaptDeclare(ISteamFriends005);
AdaptDefine(ISteamFriends005, IClientFriendsMap, "SteamFriends005") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptEmpty(IClientFriendsMap::GetFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
};
AdaptDeclare(ISteamFriends006);
AdaptDefine(ISteamFriends006, IClientFriendsMap, "SteamFriends006") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptEmpty(IClientFriendsMap::GetFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
};
AdaptDeclare(ISteamFriends007);
AdaptDefine(ISteamFriends007, IClientFriendsMap, "SteamFriends007") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
};
AdaptDeclare(ISteamFriends008);
AdaptDefine(ISteamFriends008, IClientFriendsMap, "SteamFriends008") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
};
AdaptDeclare(ISteamFriends009);
AdaptDefine(ISteamFriends009, IClientFriendsMap, "SteamFriends009") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
};
AdaptDeclare(ISteamFriends010);
AdaptDefine(ISteamFriends010, IClientFriendsMap, "SteamFriends010") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
};
AdaptDeclare(ISteamFriends011);
AdaptDefine(ISteamFriends011, IClientFriendsMap, "SteamFriends011") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
};
AdaptDeclare(ISteamFriends012);
AdaptDefine(ISteamFriends012, IClientFriendsMap, "SteamFriends012") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
};
AdaptDeclare(ISteamFriends013);
AdaptDefine(ISteamFriends013, IClientFriendsMap, "SteamFriends013") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
};
AdaptDeclare(ISteamFriends014);
AdaptDefine(ISteamFriends014, IClientFriendsMap, "SteamFriends014") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::GetPlayerNickname),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
};
AdaptDeclare(ISteamFriends015);
AdaptDefine(ISteamFriends015, IClientFriendsMap, "SteamFriends015") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::GetFriendSteamLevel),
    AdaptPassThrough(IClientFriendsMap::GetPlayerNickname),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupIDByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupName),
    AdaptEmpty(IClientFriendsMap::GetFriendsGroupMembersCount),
    AdaptEmpty(IClientFriendsMap::GetFriendsGroupMembersList),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
    AdaptPassThrough(IClientFriendsMap::IsClanPublic),
    AdaptPassThrough(IClientFriendsMap::IsClanOfficialGameGroup),
};
AdaptDeclare(ISteamFriends016);
AdaptDefine(ISteamFriends016, IClientFriendsMap, "SteamFriends016") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::GetFriendSteamLevel),
    AdaptPassThrough(IClientFriendsMap::GetPlayerNickname),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupIDByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupName),
    AdaptEmpty(IClientFriendsMap::GetFriendsGroupMembersCount),
    AdaptEmpty(IClientFriendsMap::GetFriendsGroupMembersList),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
    AdaptPassThrough(IClientFriendsMap::IsClanPublic),
    AdaptPassThrough(IClientFriendsMap::IsClanOfficialGameGroup),
    AdaptPassThrough(IClientFriendsMap::GetNumChatsWithUnreadPriorityMessages),
};
AdaptDeclare(ISteamFriends017);
AdaptDefine(ISteamFriends017, IClientFriendsMap, "SteamFriends017") = {
    AdaptPassThrough(IClientFriendsMap::GetPersonaName),
    AdaptPassThrough(IClientFriendsMap::SetPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendRelationship),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaState),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaName),
    AdaptPassThrough(IClientFriendsMap::GetFriendGamePlayed),
    AdaptPassThrough(IClientFriendsMap::GetFriendPersonaNameHistory),
    AdaptPassThrough(IClientFriendsMap::GetFriendSteamLevel),
    AdaptPassThrough(IClientFriendsMap::GetPlayerNickname),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupIDByIndex),
    AdaptPassThrough(IClientFriendsMap::GetFriendsGroupName),
    AdaptEmpty(IClientFriendsMap::GetFriendsGroupMembersCount),
    AdaptEmpty(IClientFriendsMap::GetFriendsGroupMembersList),
    AdaptPassThrough(IClientFriendsMap::HasFriend),
    AdaptPassThrough(IClientFriendsMap::GetClanCount),
    AdaptPassThrough(IClientFriendsMap::GetClanByIndex),
    AdaptPassThrough(IClientFriendsMap::GetClanName),
    AdaptPassThrough(IClientFriendsMap::GetClanTag),
    AdaptPassThrough(IClientFriendsMap::GetClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::DownloadClanActivityCounts),
    AdaptPassThrough(IClientFriendsMap::GetFriendCountFromSource),
    AdaptPassThrough(IClientFriendsMap::GetFriendFromSourceByIndex),
    AdaptPassThrough(IClientFriendsMap::IsUserInSource),
    AdaptPassThrough(IClientFriendsMap::SetInGameVoiceSpeaking),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlay),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToUser),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToWebPage),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayToStore),
    AdaptPassThrough(IClientFriendsMap::SetPlayedWith),
    AdaptPassThrough(IClientFriendsMap::ActivateGameOverlayInviteDialog),
    AdaptPassThrough(IClientFriendsMap::GetSmallFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetMediumFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::GetLargeFriendAvatar),
    AdaptPassThrough(IClientFriendsMap::RequestUserInformation),
    AdaptPassThrough(IClientFriendsMap::RequestClanOfficerList),
    AdaptPassThrough(IClientFriendsMap::GetClanOwner),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerCount),
    AdaptPassThrough(IClientFriendsMap::GetClanOfficerByIndex),
    AdaptPassThrough(IClientFriendsMap::GetUserRestrictions),
    AdaptPassThrough(IClientFriendsMap::SetRichPresence),
    AdaptPassThrough(IClientFriendsMap::ClearRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyCount),
    AdaptPassThrough(IClientFriendsMap::GetFriendRichPresenceKeyByIndex),
    AdaptPassThrough(IClientFriendsMap::RequestFriendRichPresence),
    AdaptPassThrough(IClientFriendsMap::InviteUserToGame),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriendCount),
    AdaptPassThrough(IClientFriendsMap::GetCoplayFriend),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayTime),
    AdaptPassThrough(IClientFriendsMap::GetFriendCoplayGame),
    AdaptPassThrough(IClientFriendsMap::JoinClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::LeaveClanChatRoom),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMemberCount),
    AdaptPassThrough(IClientFriendsMap::GetChatMemberByIndex),
    AdaptPassThrough(IClientFriendsMap::SendClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::GetClanChatMessage),
    AdaptPassThrough(IClientFriendsMap::IsClanChatAdmin),
    AdaptPassThrough(IClientFriendsMap::IsClanChatWindowOpenInSteam),
    AdaptPassThrough(IClientFriendsMap::OpenClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::CloseClanChatWindowInSteam),
    AdaptPassThrough(IClientFriendsMap::SetListenForFriendsMessages),
    AdaptPassThrough(IClientFriendsMap::ReplyToFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFriendMessage),
    AdaptPassThrough(IClientFriendsMap::GetFollowerCount),
    AdaptPassThrough(IClientFriendsMap::IsFollowing),
    AdaptPassThrough(IClientFriendsMap::EnumerateFollowingList),
    AdaptPassThrough(IClientFriendsMap::IsClanPublic),
    AdaptPassThrough(IClientFriendsMap::IsClanOfficialGameGroup),
    AdaptPassThrough(IClientFriendsMap::GetNumChatsWithUnreadPriorityMessages),
};
