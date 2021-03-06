#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

#include "argonx/cmclient/cmclient.hh"
#include "argonx/cmclient/steamcrypt.hh"
#include "argonx/cmclient/steamhandlers.hh"

#include "steammessages_clientserver.pb.h"
#include "steammessages_clientserver_2.pb.h"
#include "steammessages_clientserver_friends.pb.h"
#include "steammessages_clientserver_login.pb.h"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientUser.h"
}

enum class LogonNeeds {
    none,
    steamGuard,
    twoFactor,
};

enum class LogonState {
    loggedOff,
    loggingOn,
    loggingOff,
    loggedOn,
};

namespace Steam {
// Little hacky but Argonx:: shouldnt know about implementation details that are used in Steam::
std::unordered_map<Argonx::CMClient *, UserHandle> userHandleLookup;

UserHandle LookupHandle(Argonx::CMClient *c) {
    return userHandleLookup[c];
}

void *LookupInterfaceInternal(Argonx::CMClient *c, InterfaceTarget t) {
    auto h = LookupHandle(c);
    return GetUserInterface(h, t);
}
} // namespace Steam

template <bool isServer>
class ClientUserMap : public Reference::IClientUser {
    UserHandle userHandle;

public:
    // This should only be used on the server
    Argonx::CMClient *cmClient;
    bool              threadRunning = true;
    std::thread       bThread;

    static void backgroundThread(Argonx::CMClient *c, bool &shouldRun) {
        // Make sure this is only called from server code!
        AssertServer();
        char nameBuffer[255];
        sprintf(nameBuffer, "user %d cm", LookupHandle(c));
        loguru::set_thread_name(nameBuffer);

        while (shouldRun) {
            c->RunFrame();
        }
    }

public:
    // Logon information and handling

    LogonState logonState;

    // TODO: use a secure string thing
    std::string username;
    std::string password;
    std::string email;

    // Additional security codes that we might need
    std::string twoFactorCode;
    std::string steamGuardCode;

    // Should match the cmclients steamid!
    Argonx::SteamId &SteamId() {
        AssertServer();
        Assert(cmClient, "Valid cmclient needed for SteamId!");
        return cmClient->steamId;
    }

    DefineHelperHandler(OnMachineAuth) {
        auto  userHandle = LookupHandle(c);
        auto  msg        = b.ReadAsProto<CMsgClientUpdateMachineAuth>(msgSize);
        auto &bytes      = msg.bytes();

        auto sha = Argonx::SteamCrypt::SHA1MachineAuth(bytes);

        CMsgClientUpdateMachineAuthResponse r;
        r.set_sha_file(sha.Read(0), sha.Size());
        r.set_eresult((u32)Argonx::EResult::OK);
        r.set_cubwrote(msg.cubtowrite());
        r.set_offset(msg.offset());
        r.set_getlasterror(0);
        r.set_filesize(bytes.length());
        r.set_otp_identifier(msg.otp_identifier());

        c->WriteMessage(Argonx::EMsg::ClientUpdateMachineAuthResponse, r, jobId);

        // TODO: write sha file to disk

        // printf("[%d] OnMachineAuth", userHandle);
    }

    DefineHelperHandler(OnClientLogon) {
        auto logonResp = b.ReadAsProto<CMsgClientLogonResponse>(msgSize);
        auto eresult   = static_cast<Argonx::EResult>(logonResp.eresult());

        LOG_F(INFO, "Logon result: %d (extended %d)", eresult, logonResp.eresult_extended());
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        if (eresult == Argonx::EResult::OK) {
            c->ResetClientHeartbeat(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::seconds(logonResp.out_of_game_heartbeat_seconds())));

            user->logonState = LogonState::loggedOn;
        } else {
            // After you fail a login you need to get a new cm
            c->TryAnotherCM();
            user->logonState = LogonState::loggedOff;

            using namespace std::chrono_literals;
            c->ResetClientHeartbeat(0ms);
        }
    }

    DefineHelperHandler(OnLoginKey) {
        auto proto = b.ReadAsProto<CMsgClientNewLoginKey>(msgSize);

        CMsgClientNewLoginKeyAccepted ack;
        ack.set_unique_id(proto.unique_id());

        c->WriteMessage(Argonx::EMsg::ClientNewLoginKeyAccepted, ack, jobId);
    }

    static void OnAccountInfo(Argonx::CMClient *c, u32 msgSize, Buffer &b, u64 jobId) {

        LOG_F(INFO, "OnAccountInfo");
    }

    std::vector<std::string> gameConnectTokens;

    DefineHelperHandler(OnGameConnectTokens) {
        auto self = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        auto msg = b.ReadAsProto<CMsgClientGameConnectTokens>(msgSize);

        for (const auto &x : msg.tokens()) {
            self->gameConnectTokens.push_back(x);
        }
        LOG_F(INFO, "OnGameConnectTokens : %zu tokens", self->gameConnectTokens.size());
    }

    DefineHelperHandler(OnVACBanStatus) {
        auto banCount = b.Read<u32>();
        LOG_F(INFO, "OnVACBanStatus: %d", banCount);
    }

    u64 sessionToken;

    DefineHelperHandler(OnSessionToken) {
        auto msg = b.ReadAsProto<CMsgClientSessionToken>(msgSize);

        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        user->sessionToken = msg.token();
    }

    DefineHelperHandler(OnIsLimitedAccount) {
        auto msg  = b.ReadAsProto<CMsgClientIsLimitedAccount>(msgSize);
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        LOG_F(INFO, "OnIsLimitedAccount %s", msg.DebugString().c_str());
    }
    DefineHelperHandler(OnEmailAddrInfo) {
        auto msg  = b.ReadAsProto<CMsgClientEmailAddrInfo>(msgSize);
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        LOG_F(INFO, "OnEmailAddrInfo %s", msg.DebugString().c_str());
    }
    DefineHelperHandler(OnPlayerNicknameList) {
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);
        LOG_F(INFO, "OnPlayerNicknameList");
    }
    DefineHelperHandler(OnUpdateGuestPassesList) {
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);
        LOG_F(INFO, "OnUpdateGuestPassesList");
    }
    DefineHelperHandler(OnWalletInfoUpdate) {
        auto msg  = b.ReadAsProto<CMsgClientWalletInfoUpdate>(msgSize);
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        LOG_F(INFO, "OnWalletInfoUpdate %s", msg.DebugString().c_str());
    }

    DefineHelperHandler(OnCMList) {
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);
        LOG_F(INFO, "OnCMList");
    }

    DefineHelperHandler(OnRequestedClientStats) {
        auto msg  = b.ReadAsProto<CMsgClientRequestedClientStats>(msgSize);
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        LOG_F(INFO, "OnRequestedClientStats %s", msg.DebugString().c_str());
    }

    DefineHelperHandler(OnFriendsGroupsList) {
        auto msg  = b.ReadAsProto<CMsgClientFriendsGroupsList>(msgSize);
        auto user = LookupInterface<ClientUserMap<true>>(c, InterfaceTarget::user);

        LOG_F(INFO, "OnFriendsGroupsList %s", msg.DebugString().c_str());
    }

    void LogonInternal() {
        AssertServer();

        logonState = LogonState::loggingOn;

        CMsgClientLogon c;
        c.set_account_name(username);
        c.set_password(password);
        c.set_protocol_version(65575);

        if (twoFactorCode != "") c.set_two_factor_code(twoFactorCode.c_str());
        if (steamGuardCode != "") c.set_auth_code(steamGuardCode.c_str());

        // TODO: sha hash file

        cmClient->WriteMessage(Argonx::EMsg::ClientLogon, c);
    }

public:
    ClientUserMap(UserHandle h) : userHandle(h) {
        RpcRunOnServer() {
            logonState                 = LogonState::loggedOff;
            cmClient                   = new Argonx::CMClient();
            userHandleLookup[cmClient] = h;
            bThread                    = std::thread{backgroundThread, cmClient, std::ref(threadRunning)};
        }
    }

    virtual ~ClientUserMap() {
        RpcRunOnServer() {
            Defer(userHandleLookup.erase(cmClient));
            threadRunning = false;
            bThread.join();
            delete cmClient;
        }
    }

    // Inherited via IClientUser
    virtual UserHandle GetHSteamUser() override {
        return userHandle;
    }
    virtual void LogOn(CSteamID) override {
        LogonInternal();
    }
    virtual void LogOnWithPassword(char const *username, char const *password) override {
        RpcMakeCallIfClient(LogOnWithPassword, user, username, password) {
            this->username = username;
            this->password = password;

            LogonInternal();
        }
    }
    virtual unknown_ret LogOnAndCreateNewSteamAccountIfNeeded() override {
        return unknown_ret();
    }
    virtual unknown_ret VerifyOfflineLogon() override {
        return unknown_ret();
    }
    virtual void LogOff() override {
        RpcMakeCallIfClient(LogOff, user, ) {
            CMsgClientLogOff c;
            cmClient->WriteMessage(Argonx::EMsg::ClientLogOff, c);
        }
    }
    virtual bool BLoggedOn() override {
        RpcMakeCallIfClient(BLoggedOn, user, ) {
            return logonState == LogonState::loggedOn;
        }
    }
    virtual u32 GetLogonState() override {
        RpcMakeCallIfClient(GetLogonState, user) {
            return (u32)logonState;
        }
    }
    virtual bool BConnected() override {
        RpcMakeCallIfClient(BConnected, user, ) {
            return true;
        }
    }
    virtual bool BTryingToLogin() override {
        RpcMakeCallIfClient(BTryingToLogin, user) {
            return logonState == LogonState::loggingOn;
        }
    }
    virtual Steam::CSteamID GetSteamID() override {
        RpcMakeCallIfClient(GetSteamID, user, ) {
            return Steam::CSteamID(SteamId().steamId64);
        }
    }
    virtual Steam::CSteamID GetConsoleSteamID() override {
        // In CUser this returns a different SteamID to the actual one
        // (which is GetSteamID)

        // For now we will just return the main one
        return Steam::CSteamID(SteamId());
    }
    virtual unknown_ret GetClientInstanceID() override {
        return unknown_ret();
    }
    virtual bool IsVACBanned(Steam::CGameID appid) override {
        // Look at CClientJobVACBanStatus2::
        return false;
    }
    virtual void SetEmail(char const *email) override {
        email = email;
    }
    virtual unknown_ret SetConfigString(EConfigSubTree, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConfigString(EConfigSubTree, char const *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetConfigInt(EConfigSubTree, char const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConfigInt(EConfigSubTree, char const *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret DeleteConfigKey(EConfigSubTree, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConfigStoreKeyName(EConfigSubTree, char const *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret InitiateGameConnection(void *, int, CSteamID, CGameID, unsigned int, unsigned short, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret InitiateGameConnectionOld(void *, int, CSteamID, CGameID, unsigned int, unsigned short, bool, void *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret TerminateGameConnection(unsigned int, unsigned short) override {
        return unknown_ret();
    }
    unknown_ret SignalAppsToShutDown(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret TerminateAppMultiStep(CGameID, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSelfAsChatDestination(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IsPrimaryChatDestination() override {
        return unknown_ret();
    }
    virtual unknown_ret RequestLegacyCDKey(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret AckGuestPass(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret RedeemGuestPass(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToGiveCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToRedeemCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToGiveInfo(unsigned int, unsigned long long *, unsigned int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToGiveOut(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToRedeem(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToRedeemInfo(unsigned int, unsigned long long *, unsigned int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGuestPassToRedeemSenderName(unsigned int, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumAppsInGuestPassesToRedeem() override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppsInGuestPassesToRedeem(unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCountUserNotifications() override {
        return unknown_ret();
    }
    virtual unknown_ret GetCountUserNotification(EUserNotification) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestStoreAuthURL(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLanguage(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret TrackAppUsageEvent(CGameID, int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret RaiseConnectionPriority(EConnectionPriority, EConnectionPriorityReason) override {
        return unknown_ret();
    }
    virtual unknown_ret ResetConnectionPriority(int) override {
        return unknown_ret();
    }
    virtual unknown_ret BHasCachedCredentials(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAccountNameForCachedCredentialLogin(char const *, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret DestroyCachedCredentials(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentWebAuthToken(char *, int, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestWebAuthToken() override {
        return unknown_ret();
    }
    virtual void SetLoginInformation(char const *username, char const *password, bool rememberPassword) override {
        RpcMakeCallIfClient(SetLoginInformation, user, username, password, rememberPassword) {
            this->username = username;
            this->password = password;

            // TODO: rememberPassword?
        }
    }
    virtual void SetTwoFactorCode(char const *code) override {
        RpcMakeCallIfClient(SetTwoFactorCode, user, code) {
            twoFactorCode = code;
        }
    }
    virtual void ClearAllLoginInformation() override {
        RpcMakeCallIfClient(ClearAllLoginInformation, user, ) {
            username       = "";
            password       = "";
            twoFactorCode  = "";
            steamGuardCode = "";
        }
    }
    unknown_ret BEnableEmbeddedClient(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ResetEmbeddedClient(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BHasEmbeddedClientToken(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RequestEmbeddedClientToken(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AuthorizeNewDevice(unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetLanguage(char *, int) override {
        return unknown_ret();
    }
    unknown_ret BIsCyberCafe() override {
        return unknown_ret();
    }
    unknown_ret BIsAcademicAccount() override {
        return unknown_ret();
    }
    unknown_ret BIsPortal2EducationAccount() override {
        return unknown_ret();
    }
    unknown_ret BIsAlienwareDemoAccount() override {
        return unknown_ret();
    }
    unknown_ret TrackNatTraversalStat(CNatTraversalStat const *) override {
        return unknown_ret();
    }
    unknown_ret TrackSteamUsageEvent(ESteamUsageEvent, unsigned char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret TrackSteamGUIUsage(char const *) override {
        return unknown_ret();
    }
    unknown_ret SetComputerInUse() override {
        return unknown_ret();
    }
    unknown_ret BIsGameRunning(CGameID) override {
        return unknown_ret();
    }
    unknown_ret BIsGameWindowReady(CGameID) override {
        return unknown_ret();
    }
    unknown_ret BUpdateAppOwnershipTicket(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret RequestCustomBinary(char const *, unsigned int, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret GetCustomBinariesState(unsigned int, long long *, long long *) override {
        return unknown_ret();
    }
    unknown_ret RequestCustomBinaries(unsigned int, bool, bool, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret SetCellID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetUserBaseFolder() override {
        return unknown_ret();
    }
    unknown_ret GetUserDataFolder(CGameID, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetUserConfigFolder(char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetAccountName(char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAccountName(CSteamID, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsPasswordRemembered() override {
        return unknown_ret();
    }
    unknown_ret CheckoutSiteLicenseSeat(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAvailableSeats(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAssociatedSiteName() override {
        return unknown_ret();
    }
    unknown_ret BIsRunningInCafe() override {
        return unknown_ret();
    }
    unknown_ret BAllowCachedCredentialsInCafe() override {
        return unknown_ret();
    }
    unknown_ret RequiresLegacyCDKey(unsigned int, bool *) override {
        return unknown_ret();
    }
    unknown_ret GetLegacyCDKey(unsigned int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret SetLegacyCDKey(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret WriteLegacyCDKey(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RemoveLegacyCDKey(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RequestLegacyCDKeyFromApp(unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsAnyGameRunning() override {
        return unknown_ret();
    }
    unknown_ret GetSteamGuardDetails() override {
        return unknown_ret();
    }
    unknown_ret GetTwoFactorDetails() override {
        return unknown_ret();
    }
    unknown_ret BHasTwoFactor() override {
        return unknown_ret();
    }
    unknown_ret GetEmail(char *, int, bool *) override {
        return unknown_ret();
    }
    unknown_ret FindAccountsByCdKey(char const *) override {
        return unknown_ret();
    }
    unknown_ret Test_FakeConnectionTimeout() override {
        return unknown_ret();
    }
    unknown_ret RunInstallScript(unsigned int, char const *, bool) override {
        return unknown_ret();
    }
    unknown_ret IsInstallScriptRunning() override {
        return unknown_ret();
    }
    unknown_ret GetInstallScriptState(char *, unsigned int, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret SpawnProcess(char const *, char const *, unsigned int, char const *, CGameID, char const *, unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppOwnershipTicketLength(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppOwnershipTicketData(unsigned int, void *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppOwnershipTicketExtendedData(unsigned int, void *, unsigned int, unsigned int *, unsigned int *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetMarketingMessageCount() override {
        return unknown_ret();
    }
    unknown_ret GetMarketingMessage(int, unsigned long long *, char *, int, EMarketingMessageFlags *) override {
        return unknown_ret();
    }
    unknown_ret GetAuthSessionTicket(void *, int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret BeginAuthSession(void const *, int, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret EndAuthSession(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret CancelAuthTicket(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsUserSubscribedAppInTicket(CSteamID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AdvertiseGame(CGameID, CSteamID, unsigned int, unsigned short) override {
        return unknown_ret();
    }
    unknown_ret RequestEncryptedAppTicket(void *, int) override {
        return unknown_ret();
    }
    unknown_ret GetEncryptedAppTicket(void *, int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetGameBadgeLevel(int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetPlayerSteamLevel() override {
        return unknown_ret();
    }
    unknown_ret SetAccountLimited(bool) override {
        return unknown_ret();
    }
    unknown_ret BIsAccountLimited() override {
        return unknown_ret();
    }
    unknown_ret SetAccountCommunityBanned(bool) override {
        return unknown_ret();
    }
    unknown_ret BIsAccountCommunityBanned() override {
        return unknown_ret();
    }
    unknown_ret SetLimitedAccountCanInviteFriends(bool) override {
        return unknown_ret();
    }
    unknown_ret BLimitedAccountCanInviteFriends() override {
        return unknown_ret();
    }
    unknown_ret SendValidationEmail() override {
        return unknown_ret();
    }
    unknown_ret BGameConnectTokensAvailable() override {
        return unknown_ret();
    }
    unknown_ret NumGamesRunning() override {
        return unknown_ret();
    }
    unknown_ret GetRunningGameID(int) override {
        return unknown_ret();
    }
    unknown_ret GetRunningGamePID(int) override {
        return unknown_ret();
    }
    unknown_ret GetAccountSecurityPolicyFlags() override {
        return unknown_ret();
    }
    unknown_ret SetClientStat(EClientStat, long long, unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret VerifyPassword(char const *) override {
        return unknown_ret();
    }
    unknown_ret BSupportUser() override {
        return unknown_ret();
    }
    unknown_ret BNeedsSSANextSteamLogon() override {
        return unknown_ret();
    }
    unknown_ret ClearNeedsSSANextSteamLogon() override {
        return unknown_ret();
    }
    unknown_ret BIsAppOverlayEnabled(CGameID) override {
        return unknown_ret();
    }
    unknown_ret BOverlayIgnoreChildProcesses(CGameID) override {
        return unknown_ret();
    }
    unknown_ret BIsBehindNAT() override {
        return unknown_ret();
    }
    unknown_ret GetMicroTxnAppID(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetMicroTxnOrderID(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret BGetMicroTxnPrice(unsigned long long, CAmount *, CAmount *, bool *, CAmount *) override {
        return unknown_ret();
    }
    unknown_ret GetMicroTxnLineItemCount(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret BGetMicroTxnLineItem(unsigned long long, unsigned int, CAmount *, unsigned int *, char *, unsigned int, int *, unsigned char *, CAmount *, bool *) override {
        return unknown_ret();
    }
    unknown_ret BIsSandboxMicroTxn(unsigned long long, bool *) override {
        return unknown_ret();
    }
    unknown_ret BMicroTxnRequiresCachedPmtMethod(unsigned long long, bool *) override {
        return unknown_ret();
    }
    unknown_ret AuthorizeMicroTxn(unsigned long long, EMicroTxnAuthResponse) override {
        return unknown_ret();
    }
    unknown_ret BGetWalletBalance(bool *, CAmount *, CAmount *) override {
        return unknown_ret();
    }
    unknown_ret RequestMicroTxnInfo(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret BMicroTxnRefundable(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret BGetAppMinutesPlayed(unsigned int, int *, int *) override {
        return unknown_ret();
    }
    unknown_ret GetAppLastPlayedTime(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppUpdateDisabledSecondsRemaining(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BGetGuideURL(unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BPromptToVerifyEmail() override {
        return unknown_ret();
    }
    unknown_ret BPromptToChangePassword() override {
        return unknown_ret();
    }
    unknown_ret BAccountExtraSecurity() override {
        return unknown_ret();
    }
    unknown_ret BAccountShouldShowLockUI() override {
        return unknown_ret();
    }
    unknown_ret GetCountAuthedComputers() override {
        return unknown_ret();
    }
    unknown_ret BSteamGuardNewMachineNotification() override {
        return unknown_ret();
    }
    unknown_ret GetSteamGuardEnabledTime() override {
        return unknown_ret();
    }
    unknown_ret GetSteamGuardHistoryEntry(int, unsigned int *, unsigned int *, bool *, char *, int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret SetSteamGuardNewMachineDialogResponse(bool, bool) override {
        return unknown_ret();
    }
    unknown_ret SetPhoneIsVerified(bool) override {
        return unknown_ret();
    }
    unknown_ret BIsPhoneVerified() override {
        return unknown_ret();
    }
    unknown_ret SetPhoneIsIdentifying(bool) override {
        return unknown_ret();
    }
    unknown_ret BIsPhoneIdentifying() override {
        return unknown_ret();
    }
    unknown_ret SetPhoneIsRequiringVerification(bool) override {
        return unknown_ret();
    }
    unknown_ret BIsPhoneRequiringVerification() override {
        return unknown_ret();
    }
    unknown_ret ChangeTwoFactorAuthOptions(int) override {
        return unknown_ret();
    }
    unknown_ret Set2ndFactorAuthCode(char const *, bool) override {
        return unknown_ret();
    }
    unknown_ret SetUserMachineName(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetUserMachineName(char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetEmailDomainFromLogonFailure(char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetDurationControl() override {
        return unknown_ret();
    }
    unknown_ret GetDurationControlForApp(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsSubscribedApp(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetSubscribedApps(unsigned int *, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret RegisterActivationCode(char const *) override {
        return unknown_ret();
    }
    unknown_ret AckSystemIM(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret RequestSpecialSurvey(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SendSpecialSurveyResponse(unsigned int, unsigned char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RequestNotifications() override {
        return unknown_ret();
    }
    unknown_ret GetAppOwnershipInfo(unsigned int, unsigned int *, unsigned int *, char *) override {
        return unknown_ret();
    }
    unknown_ret SendGameWebCallback(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret BIsStreamingUIToRemoteDevice() override {
        return unknown_ret();
    }
    unknown_ret BIsCurrentlyNVStreaming() override {
        return unknown_ret();
    }
    unknown_ret OnBigPictureForStreamingStartResult(bool, void *) override {
        return unknown_ret();
    }
    unknown_ret OnBigPictureForStreamingDone() override {
        return unknown_ret();
    }
    unknown_ret OnBigPictureForStreamingRestarting() override {
        return unknown_ret();
    }
    unknown_ret StopStreaming(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret LockParentalLock() override {
        return unknown_ret();
    }
    unknown_ret UnlockParentalLock(char const *) override {
        return unknown_ret();
    }
    unknown_ret BIsParentalLockEnabled() override {
        return unknown_ret();
    }
    unknown_ret BIsParentalLockLocked() override {
        return unknown_ret();
    }
    unknown_ret BlockApp(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret UnblockApp(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsAppBlocked(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsAppInBlockList(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BlockFeature(EParentalFeature) override {
        return unknown_ret();
    }
    unknown_ret UnblockFeature(EParentalFeature) override {
        return unknown_ret();
    }
    unknown_ret BIsFeatureBlocked(EParentalFeature) override {
        return unknown_ret();
    }
    unknown_ret BIsFeatureInBlockList(EParentalFeature) override {
        return unknown_ret();
    }
    unknown_ret GetParentalUnlockTime() override {
        return unknown_ret();
    }
    unknown_ret BGetRecoveryEmail(char *, int) override {
        return unknown_ret();
    }
    unknown_ret RequestParentalRecoveryEmail() override {
        return unknown_ret();
    }
    unknown_ret BIsLockFromSiteLicense() override {
        return unknown_ret();
    }
    unknown_ret BGetSerializedParentalSettings(CUtlBuffer *) override {
        return unknown_ret();
    }
    unknown_ret BSetParentalSettings(CUtlBuffer *) override {
        return unknown_ret();
    }
    unknown_ret BDisableParentalSettings() override {
        return unknown_ret();
    }
    unknown_ret BGetParentalWebToken(CUtlBuffer *, CUtlBuffer *) override {
        return unknown_ret();
    }
    unknown_ret GetCommunityPreference(ECommunityPreference) override {
        return unknown_ret();
    }
    unknown_ret SetCommunityPreference(ECommunityPreference, bool) override {
        return unknown_ret();
    }
    unknown_ret BCanLogonOfflineMode() override {
        return unknown_ret();
    }
    unknown_ret LogOnOfflineMode() override {
        return unknown_ret();
    }
    unknown_ret ValidateOfflineLogonTicket(char const *) override {
        return unknown_ret();
    }
    unknown_ret BGetOfflineLogonTicket(char const *, COffline_OfflineLogonTicket *) override {
        return unknown_ret();
    }
    unknown_ret UploadLocalClientLogs() override {
        return unknown_ret();
    }
    unknown_ret SetAsyncNotificationEnabled(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret BIsOtherSessionPlaying(unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret BKickOtherPlayingSession() override {
        return unknown_ret();
    }
    unknown_ret BIsAccountLockedDown() override {
        return unknown_ret();
    }
    unknown_ret ClearAndSetAppTags(CGameID, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    unknown_ret RemoveAppTag(CGameID, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddAppTag(CGameID, char const *) override {
        return unknown_ret();
    }
    unknown_ret ClearAppTags(CGameID) override {
        return unknown_ret();
    }
    unknown_ret SetAppHidden(CGameID, bool) override {
        return unknown_ret();
    }
    unknown_ret RequestAccountLinkInfo() override {
        return unknown_ret();
    }
    unknown_ret RequestSurveySchedule() override {
        return unknown_ret();
    }
    unknown_ret RequestNewSteamAnnouncementState() override {
        return unknown_ret();
    }
    unknown_ret UpdateSteamAnnouncementLastRead(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetMarketEligibility() override {
        return unknown_ret();
    }
    unknown_ret UpdateGameVrDllState(CGameID, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret BIsAnyGameOrServiceAppRunning() override {
        return unknown_ret();
    }
    unknown_ret BGetAppArrayMinutesPlayed(unsigned int *, int, int *, int *) override {
        return unknown_ret();
    }
    unknown_ret BGetAppsLastPlayedTime(unsigned int *, int, unsigned int *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientUserMap, "SteamUser");

// Handler registering
RegisterHelperUnique(Argonx::EMsg::ClientLogOnResponse, ClientUserMap<true>::OnClientLogon);
RegisterHelperUnique(Argonx::EMsg::ClientUpdateMachineAuth, ClientUserMap<true>::OnMachineAuth);
RegisterHelperUnique(Argonx::EMsg::ClientNewLoginKey, ClientUserMap<true>::OnLoginKey);
RegisterHelperUnique(Argonx::EMsg::ClientGameConnectTokens, ClientUserMap<true>::OnGameConnectTokens);
RegisterHelperUnique(Argonx::EMsg::ClientAccountInfo, ClientUserMap<true>::OnAccountInfo);
RegisterHelperUnique(Argonx::EMsg::ClientVACBanStatus, ClientUserMap<true>::OnVACBanStatus);
RegisterHelperUnique(Argonx::EMsg::ClientIsLimitedAccount, ClientUserMap<true>::OnIsLimitedAccount);
RegisterHelperUnique(Argonx::EMsg::ClientEmailAddrInfo, ClientUserMap<true>::OnEmailAddrInfo);
RegisterHelperUnique(Argonx::EMsg::ClientPlayerNicknameList, ClientUserMap<true>::OnPlayerNicknameList); // Should probably be handled by friends
RegisterHelperUnique(Argonx::EMsg::ClientUpdateGuestPassesList, ClientUserMap<true>::OnUpdateGuestPassesList);
RegisterHelperUnique(Argonx::EMsg::ClientWalletInfoUpdate, ClientUserMap<true>::OnWalletInfoUpdate);
RegisterHelperUnique(Argonx::EMsg::ClientSessionToken, ClientUserMap<true>::OnSessionToken);
RegisterHelperUnique(Argonx::EMsg::ClientCMList, ClientUserMap<true>::OnCMList);
RegisterHelperUnique(Argonx::EMsg::ClientRequestedClientStats, ClientUserMap<true>::OnRequestedClientStats);
RegisterHelperUnique(Argonx::EMsg::ClientFriendsGroupsList, ClientUserMap<true>::OnFriendsGroupsList); // Should probably be handled by friends

using IClientUserMap = ClientUserMap<false>;

AdaptDeclare(ISteamUser004);
AdaptDefine(ISteamUser004, IClientUserMap, "SteamUser004") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::LogOn),
    AdaptPassThrough(IClientUserMap::LogOff),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetLogonState),
    AdaptPassThrough(IClientUserMap::BConnected),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::IsVACBanned),
    AdaptEmpty(IClientUserMap::RequireShowVACBannedMessage),
    AdaptEmpty(IClientUserMap::AcknowledgeVACBanning),
    AdaptEmpty(IClientUserMap::NClientGameIDAdd),
    AdaptEmpty(IClientUserMap::RemoveClientGame),
    AdaptEmpty(IClientUserMap::SetClientGameServer),
    AdaptEmpty(IClientUserMap::SetSteam2Ticket),
    AdaptEmpty(IClientUserMap::AddServerNetAddress),
    AdaptPassThrough(IClientUserMap::SetEmail),
    AdaptEmpty(IClientUserMap::GetSteamGameConnectToken),
    AdaptPassThrough(IClientUserMap::SetConfigString),
    AdaptPassThrough(IClientUserMap::GetConfigString),
    AdaptPassThrough(IClientUserMap::SetConfigInt),
    AdaptPassThrough(IClientUserMap::GetConfigInt),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::SetSelfAsChatDestination),
    AdaptPassThrough(IClientUserMap::IsPrimaryChatDestination),
    AdaptPassThrough(IClientUserMap::RequestLegacyCDKey),
};
AdaptDeclare(ISteamUser005);
AdaptDefine(ISteamUser005, IClientUserMap, "SteamUser005") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::LogOn),
    AdaptPassThrough(IClientUserMap::LogOff),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetLogonState),
    AdaptPassThrough(IClientUserMap::BConnected),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::IsVACBanned),
    AdaptEmpty(IClientUserMap::RequireShowVACBannedMessage),
    AdaptEmpty(IClientUserMap::AcknowledgeVACBanning),
    AdaptEmpty(IClientUserMap::SetSteam2Ticket),
    AdaptEmpty(IClientUserMap::AddServerNetAddress),
    AdaptPassThrough(IClientUserMap::SetEmail),
    AdaptPassThrough(IClientUserMap::SetConfigString),
    AdaptPassThrough(IClientUserMap::GetConfigString),
    AdaptPassThrough(IClientUserMap::SetConfigInt),
    AdaptPassThrough(IClientUserMap::GetConfigInt),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::SetSelfAsChatDestination),
    AdaptPassThrough(IClientUserMap::IsPrimaryChatDestination),
    AdaptPassThrough(IClientUserMap::RequestLegacyCDKey),
    AdaptEmpty(IClientUserMap::SendGuestPassByEmail),
    AdaptEmpty(IClientUserMap::SendGuestPassByAccountID),
    AdaptPassThrough(IClientUserMap::AckGuestPass),
    AdaptPassThrough(IClientUserMap::RedeemGuestPass),
    AdaptPassThrough(IClientUserMap::GetGuestPassToGiveCount),
    AdaptPassThrough(IClientUserMap::GetGuestPassToRedeemCount),
    AdaptEmpty(IClientUserMap::GetGuestPassLastUpdateTime),
    AdaptPassThrough(IClientUserMap::GetGuestPassToGiveInfo),
    AdaptPassThrough(IClientUserMap::GetGuestPassToRedeemInfo),
    AdaptEmpty(IClientUserMap::GetGuestPassToRedeemSenderAddress),
    AdaptPassThrough(IClientUserMap::GetGuestPassToRedeemSenderName),
    AdaptEmpty(IClientUserMap::AcknowledgeMessageByGID),
    AdaptPassThrough(IClientUserMap::SetLanguage),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptEmpty(IClientUserMap::SetAccountName),
    AdaptEmpty(IClientUserMap::SetPassword),
    AdaptEmpty(IClientUserMap::SetAccountCreationTime),
};
AdaptDeclare(ISteamUser006);
AdaptDefine(ISteamUser006, IClientUserMap, "SteamUser006") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::LogOn),
    AdaptPassThrough(IClientUserMap::LogOff),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::SetConfigString),
    AdaptPassThrough(IClientUserMap::GetConfigString),
    AdaptPassThrough(IClientUserMap::SetConfigInt),
    AdaptPassThrough(IClientUserMap::GetConfigInt),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
};
AdaptDeclare(ISteamUser007);
AdaptDefine(ISteamUser007, IClientUserMap, "SteamUser007") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::LogOn),
    AdaptPassThrough(IClientUserMap::LogOff),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::SetConfigString),
    AdaptPassThrough(IClientUserMap::GetConfigString),
    AdaptPassThrough(IClientUserMap::SetConfigInt),
    AdaptPassThrough(IClientUserMap::GetConfigInt),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptEmpty(IClientUserMap::RefreshSteam2Login),
};
AdaptDeclare(ISteamUser008);
AdaptDefine(ISteamUser008, IClientUserMap, "SteamUser008") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptEmpty(IClientUserMap::RefreshSteam2Login),
};
AdaptDeclare(ISteamUser009);
AdaptDefine(ISteamUser009, IClientUserMap, "SteamUser009") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptEmpty(IClientUserMap::RefreshSteam2Login),
};
AdaptDeclare(ISteamUser010);
AdaptDefine(ISteamUser010, IClientUserMap, "SteamUser010") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
};
AdaptDeclare(ISteamUser011);
AdaptDefine(ISteamUser011, IClientUserMap, "SteamUser011") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetCompressedVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
};
AdaptDeclare(ISteamUser012);
AdaptDefine(ISteamUser012, IClientUserMap, "SteamUser012") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetCompressedVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
};
AdaptDeclare(ISteamUser013);
AdaptDefine(ISteamUser013, IClientUserMap, "SteamUser013") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
};
AdaptDeclare(ISteamUser014);
AdaptDefine(ISteamUser014, IClientUserMap, "SteamUser014") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
};
AdaptDeclare(ISteamUser015);
AdaptDefine(ISteamUser015, IClientUserMap, "SteamUser015") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptEmpty(IClientUserMap::GetVoiceOptimalSampleRate),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
};
AdaptDeclare(ISteamUser016);
AdaptDefine(ISteamUser016, IClientUserMap, "SteamUser016") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptEmpty(IClientUserMap::GetVoiceOptimalSampleRate),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
};
AdaptDeclare(ISteamUser017);
AdaptDefine(ISteamUser017, IClientUserMap, "SteamUser017") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptEmpty(IClientUserMap::GetVoiceOptimalSampleRate),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetGameBadgeLevel),
    AdaptPassThrough(IClientUserMap::GetPlayerSteamLevel),
};
AdaptDeclare(ISteamUser018);
AdaptDefine(ISteamUser018, IClientUserMap, "SteamUser018") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptEmpty(IClientUserMap::GetVoiceOptimalSampleRate),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetGameBadgeLevel),
    AdaptPassThrough(IClientUserMap::GetPlayerSteamLevel),
    AdaptPassThrough(IClientUserMap::RequestStoreAuthURL),
};
AdaptDeclare(ISteamUser019);
AdaptDefine(ISteamUser019, IClientUserMap, "SteamUser019") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptEmpty(IClientUserMap::GetVoiceOptimalSampleRate),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetGameBadgeLevel),
    AdaptPassThrough(IClientUserMap::GetPlayerSteamLevel),
    AdaptPassThrough(IClientUserMap::RequestStoreAuthURL),
    AdaptPassThrough(IClientUserMap::BIsPhoneVerified),
    AdaptPassThrough(IClientUserMap::BHasTwoFactor),
    AdaptPassThrough(IClientUserMap::BIsPhoneIdentifying),
    AdaptPassThrough(IClientUserMap::BIsPhoneRequiringVerification),
};
AdaptDeclare(ISteamUser020);
AdaptDefine(ISteamUser020, IClientUserMap, "SteamUser020") = {
    AdaptPassThrough(IClientUserMap::GetHSteamUser),
    AdaptPassThrough(IClientUserMap::BLoggedOn),
    AdaptPassThrough(IClientUserMap::GetSteamID),
    AdaptPassThrough(IClientUserMap::InitiateGameConnection),
    AdaptPassThrough(IClientUserMap::TerminateGameConnection),
    AdaptPassThrough(IClientUserMap::TrackAppUsageEvent),
    AdaptPassThrough(IClientUserMap::GetUserDataFolder),
    AdaptEmpty(IClientUserMap::StartVoiceRecording),
    AdaptEmpty(IClientUserMap::StopVoiceRecording),
    AdaptEmpty(IClientUserMap::GetAvailableVoice),
    AdaptEmpty(IClientUserMap::GetVoice),
    AdaptEmpty(IClientUserMap::DecompressVoice),
    AdaptEmpty(IClientUserMap::GetVoiceOptimalSampleRate),
    AdaptPassThrough(IClientUserMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientUserMap::BeginAuthSession),
    AdaptPassThrough(IClientUserMap::EndAuthSession),
    AdaptPassThrough(IClientUserMap::CancelAuthTicket),
    AdaptPassThrough(IClientUserMap::IsUserSubscribedAppInTicket),
    AdaptPassThrough(IClientUserMap::BIsBehindNAT),
    AdaptPassThrough(IClientUserMap::AdvertiseGame),
    AdaptPassThrough(IClientUserMap::RequestEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetEncryptedAppTicket),
    AdaptPassThrough(IClientUserMap::GetGameBadgeLevel),
    AdaptPassThrough(IClientUserMap::GetPlayerSteamLevel),
    AdaptPassThrough(IClientUserMap::RequestStoreAuthURL),
    AdaptPassThrough(IClientUserMap::BIsPhoneVerified),
    AdaptPassThrough(IClientUserMap::BHasTwoFactor),
    AdaptPassThrough(IClientUserMap::BIsPhoneIdentifying),
    AdaptPassThrough(IClientUserMap::BIsPhoneRequiringVerification),
    AdaptPassThrough(IClientUserMap::GetMarketEligibility),
};
