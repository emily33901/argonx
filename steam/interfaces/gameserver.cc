#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientGameServer.h"
}

template<bool isServer>
class ClientGameServerMap : public Reference::IClientGameServer {
public:
    // Inherited via IClientGameServer
    virtual unknown_ret GetHSteamUser() override {
        return unknown_ret();
    }
    virtual unknown_ret InitGameServer(unsigned int, unsigned short, unsigned short, unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetProduct(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetGameDescription(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetModDir(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDedicatedServer(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret LogOn(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret LogOnAnonymous() override {
        return unknown_ret();
    }
    virtual unknown_ret LogOff() override {
        return unknown_ret();
    }
    virtual unknown_ret GetSteamID() override {
        return unknown_ret();
    }
    virtual unknown_ret BLoggedOn() override {
        return unknown_ret();
    }
    virtual unknown_ret BSecure() override {
        return unknown_ret();
    }
    virtual unknown_ret WasRestartRequested() override {
        return unknown_ret();
    }
    virtual unknown_ret SetMaxPlayerCount(int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetBotPlayerCount(int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetServerName(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetMapName(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetPasswordProtected(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSpectatorPort(unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSpectatorServerName(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearAllKeyValues() override {
        return unknown_ret();
    }
    virtual unknown_ret SetKeyValue(char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetGameTags(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetGameData(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetRegion(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SendUserConnectAndAuthenticate(unsigned int, void const *, unsigned int, CSteamID *) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateUnauthenticatedUserConnection() override {
        return unknown_ret();
    }
    virtual unknown_ret SendUserDisconnect(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret BUpdateUserData(CSteamID, char const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAuthSessionTicket(void *, int, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret BeginAuthSession(void const *, int, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret EndAuthSession(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret CancelAuthTicket(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsUserSubscribedAppInTicket(CSteamID, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestUserGroupStatus(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGameplayStats() override {
        return unknown_ret();
    }
    virtual unknown_ret GetServerReputation() override {
        return unknown_ret();
    }
    virtual unknown_ret GetPublicIP() override {
        return unknown_ret();
    }
    virtual unknown_ret HandleIncomingPacket(void const *, int, unsigned int, unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNextOutgoingPacket(void *, int, unsigned int *, unsigned short *) override {
        return unknown_ret();
    }
    virtual unknown_ret EnableHeartbeats(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetHeartbeatInterval(int) override {
        return unknown_ret();
    }
    virtual unknown_ret ForceHeartbeat() override {
        return unknown_ret();
    }
    virtual unknown_ret GetLogonState() override {
        return unknown_ret();
    }
    virtual unknown_ret BConnected() override {
        return unknown_ret();
    }
    virtual unknown_ret RaiseConnectionPriority(EConnectionPriority) override {
        return unknown_ret();
    }
    virtual unknown_ret ResetConnectionPriority(int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetCellID(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret TrackSteamUsageEvent(ESteamUsageEvent, unsigned char const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetCountOfSimultaneousGuestUsersPerSteamAccount(int) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateConnectedUsers(int, ConnectedUserInfo_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret AssociateWithClan(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret ComputeNewPlayerCompatibility(CSteamID) override {
        return unknown_ret();
    }
    virtual unknown_ret _BGetUserAchievementStatus(CSteamID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSSetSpawnCount(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSGetSteam2GetEncryptionKeyToSendToNewClient(void *, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSSendSteam2UserConnect(unsigned int, void const *, unsigned int, unsigned int, unsigned short, void const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSSendSteam3UserConnect(CSteamID, unsigned int, void const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSSendUserConnect(unsigned int, unsigned int, unsigned short, void const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSRemoveUserConnect(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSUpdateStatus(int, int, int, char const *, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSCreateUnauthenticatedUser(CSteamID *) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSSetServerType(int, unsigned int, unsigned int, unsigned short, unsigned short, unsigned short, char const *, char const *, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret _SetBasicServerData(unsigned short, bool, char const *, char const *, unsigned short, bool, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret _GSSendUserDisconnect(CSteamID, unsigned int) override {
        return unknown_ret();
    }
};

using IClientGameServerMap = ClientGameServerMap<false>;

AdaptDeclare(ISteamGameServer002);
AdaptDefine(ISteamGameServer002, IClientGameServerMap, "SteamGameServer002") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::_GSSetSpawnCount),
    AdaptPassThrough(IClientGameServerMap::_GSGetSteam2GetEncryptionKeyToSendToNewClient),
    AdaptPassThrough(IClientGameServerMap::_GSSendSteam2UserConnect),
    AdaptPassThrough(IClientGameServerMap::_GSSendSteam3UserConnect),
    AdaptPassThrough(IClientGameServerMap::_GSRemoveUserConnect),
    AdaptPassThrough(IClientGameServerMap::_GSSendUserDisconnect),
    AdaptEmpty(IClientGameServerMap::GSSendUserStatusResponse),
    AdaptEmpty(IClientGameServerMap::Obsolete_GSSetStatus),
    AdaptPassThrough(IClientGameServerMap::_GSUpdateStatus),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptEmpty(IClientGameServerMap::_GSSetServerType),
    AdaptPassThrough(IClientGameServerMap::_GSSetServerType),
    AdaptPassThrough(IClientGameServerMap::_GSUpdateStatus),
    AdaptPassThrough(IClientGameServerMap::_GSCreateUnauthenticatedUser),
    AdaptEmpty(IClientGameServerMap::_GSSetUserData),
    AdaptEmpty(IClientGameServerMap::_GSUpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::_GSSetGameType),
};
AdaptDeclare(ISteamGameServer003);
AdaptDefine(ISteamGameServer003, IClientGameServerMap, "SteamGameServer003") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::_GSGetSteam2GetEncryptionKeyToSendToNewClient),
    AdaptPassThrough(IClientGameServerMap::_GSSendUserConnect),
    AdaptPassThrough(IClientGameServerMap::_GSRemoveUserConnect),
    AdaptPassThrough(IClientGameServerMap::_GSSendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::_GSSetSpawnCount),
    AdaptPassThrough(IClientGameServerMap::_GSSetServerType),
    AdaptPassThrough(IClientGameServerMap::_GSUpdateStatus),
    AdaptPassThrough(IClientGameServerMap::_GSCreateUnauthenticatedUser),
    AdaptEmpty(IClientGameServerMap::_GSSetUserData),
    AdaptEmpty(IClientGameServerMap::_GSUpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::_GSSetGameType),
    AdaptEmpty(IClientGameServerMap::_GSGetUserAchievementStatus),
};
AdaptDeclare(ISteamGameServer004);
AdaptDefine(ISteamGameServer004, IClientGameServerMap, "SteamGameServer004") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::SetGameType),
    AdaptEmpty(IClientGameServerMap::BGetUserAchievementStatus),
};
AdaptDeclare(ISteamGameServer005);
AdaptDefine(ISteamGameServer005, IClientGameServerMap, "SteamGameServer005") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::SetGameType),
    AdaptEmpty(IClientGameServerMap::BGetUserAchievementStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
};
AdaptDeclare(ISteamGameServer006);
AdaptDefine(ISteamGameServer006, IClientGameServerMap, "SteamGameServer006") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::SetGameType),
    AdaptEmpty(IClientGameServerMap::BGetUserAchievementStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
};
AdaptDeclare(ISteamGameServer007);
AdaptDefine(ISteamGameServer007, IClientGameServerMap, "SteamGameServer007") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::SetGameType),
    AdaptEmpty(IClientGameServerMap::BGetUserAchievementStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
    AdaptPassThrough(IClientGameServerMap::RequestUserGroupStatus),
};
AdaptDeclare(ISteamGameServer008);
AdaptDefine(ISteamGameServer008, IClientGameServerMap, "SteamGameServer008") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::SetGameType),
    AdaptEmpty(IClientGameServerMap::BGetUserAchievementStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
    AdaptPassThrough(IClientGameServerMap::RequestUserGroupStatus),
    AdaptPassThrough(IClientGameServerMap::GetPublicIP),
};
AdaptDeclare(ISteamGameServer009);
AdaptDefine(ISteamGameServer009, IClientGameServerMap, "SteamGameServer009") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptEmpty(IClientGameServerMap::SetGameType),
    AdaptEmpty(IClientGameServerMap::BGetUserAchievementStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
    AdaptPassThrough(IClientGameServerMap::RequestUserGroupStatus),
    AdaptPassThrough(IClientGameServerMap::GetPublicIP),
    AdaptPassThrough(IClientGameServerMap::SetGameData),
    AdaptEmpty(IClientGameServerMap::UserHasLicenseForApp),
};
AdaptDeclare(ISteamGameServer010);
AdaptDefine(ISteamGameServer010, IClientGameServerMap, "SteamGameServer010") = {
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptEmpty(IClientGameServerMap::BSetServerType),
    AdaptEmpty(IClientGameServerMap::UpdateServerStatus),
    AdaptEmpty(IClientGameServerMap::UpdateSpectatorPort),
    AdaptPassThrough(IClientGameServerMap::SetGameTags),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
    AdaptPassThrough(IClientGameServerMap::GetServerReputation),
    AdaptPassThrough(IClientGameServerMap::RequestUserGroupStatus),
    AdaptPassThrough(IClientGameServerMap::GetPublicIP),
    AdaptPassThrough(IClientGameServerMap::SetGameData),
    AdaptEmpty(IClientGameServerMap::UserHasLicenseForApp),
    AdaptPassThrough(IClientGameServerMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientGameServerMap::BeginAuthSession),
    AdaptPassThrough(IClientGameServerMap::EndAuthSession),
    AdaptPassThrough(IClientGameServerMap::CancelAuthTicket),
};
AdaptDeclare(ISteamGameServer011);
AdaptDefine(ISteamGameServer011, IClientGameServerMap, "SteamGameServer011") = {
    AdaptPassThrough(IClientGameServerMap::InitGameServer),
    AdaptPassThrough(IClientGameServerMap::SetProduct),
    AdaptPassThrough(IClientGameServerMap::SetGameDescription),
    AdaptPassThrough(IClientGameServerMap::SetModDir),
    AdaptPassThrough(IClientGameServerMap::SetDedicatedServer),
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOnAnonymous),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::WasRestartRequested),
    AdaptPassThrough(IClientGameServerMap::SetMaxPlayerCount),
    AdaptPassThrough(IClientGameServerMap::SetBotPlayerCount),
    AdaptPassThrough(IClientGameServerMap::SetServerName),
    AdaptPassThrough(IClientGameServerMap::SetMapName),
    AdaptPassThrough(IClientGameServerMap::SetPasswordProtected),
    AdaptPassThrough(IClientGameServerMap::SetSpectatorPort),
    AdaptPassThrough(IClientGameServerMap::SetSpectatorServerName),
    AdaptPassThrough(IClientGameServerMap::ClearAllKeyValues),
    AdaptPassThrough(IClientGameServerMap::SetKeyValue),
    AdaptPassThrough(IClientGameServerMap::SetGameTags),
    AdaptPassThrough(IClientGameServerMap::SetGameData),
    AdaptPassThrough(IClientGameServerMap::SetRegion),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptPassThrough(IClientGameServerMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientGameServerMap::BeginAuthSession),
    AdaptPassThrough(IClientGameServerMap::EndAuthSession),
    AdaptPassThrough(IClientGameServerMap::CancelAuthTicket),
    AdaptEmpty(IClientGameServerMap::UserHasLicenseForApp),
    AdaptPassThrough(IClientGameServerMap::RequestUserGroupStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
    AdaptPassThrough(IClientGameServerMap::GetServerReputation),
    AdaptPassThrough(IClientGameServerMap::GetPublicIP),
    AdaptPassThrough(IClientGameServerMap::HandleIncomingPacket),
    AdaptPassThrough(IClientGameServerMap::GetNextOutgoingPacket),
    AdaptPassThrough(IClientGameServerMap::EnableHeartbeats),
    AdaptPassThrough(IClientGameServerMap::SetHeartbeatInterval),
    AdaptPassThrough(IClientGameServerMap::ForceHeartbeat),
    AdaptPassThrough(IClientGameServerMap::AssociateWithClan),
    AdaptPassThrough(IClientGameServerMap::ComputeNewPlayerCompatibility),
};
AdaptDeclare(ISteamGameServer012);
AdaptDefine(ISteamGameServer012, IClientGameServerMap, "SteamGameServer012") = {
    AdaptPassThrough(IClientGameServerMap::InitGameServer),
    AdaptPassThrough(IClientGameServerMap::SetProduct),
    AdaptPassThrough(IClientGameServerMap::SetGameDescription),
    AdaptPassThrough(IClientGameServerMap::SetModDir),
    AdaptPassThrough(IClientGameServerMap::SetDedicatedServer),
    AdaptPassThrough(IClientGameServerMap::LogOn),
    AdaptPassThrough(IClientGameServerMap::LogOnAnonymous),
    AdaptPassThrough(IClientGameServerMap::LogOff),
    AdaptPassThrough(IClientGameServerMap::BLoggedOn),
    AdaptPassThrough(IClientGameServerMap::BSecure),
    AdaptPassThrough(IClientGameServerMap::GetSteamID),
    AdaptPassThrough(IClientGameServerMap::WasRestartRequested),
    AdaptPassThrough(IClientGameServerMap::SetMaxPlayerCount),
    AdaptPassThrough(IClientGameServerMap::SetBotPlayerCount),
    AdaptPassThrough(IClientGameServerMap::SetServerName),
    AdaptPassThrough(IClientGameServerMap::SetMapName),
    AdaptPassThrough(IClientGameServerMap::SetPasswordProtected),
    AdaptPassThrough(IClientGameServerMap::SetSpectatorPort),
    AdaptPassThrough(IClientGameServerMap::SetSpectatorServerName),
    AdaptPassThrough(IClientGameServerMap::ClearAllKeyValues),
    AdaptPassThrough(IClientGameServerMap::SetKeyValue),
    AdaptPassThrough(IClientGameServerMap::SetGameTags),
    AdaptPassThrough(IClientGameServerMap::SetGameData),
    AdaptPassThrough(IClientGameServerMap::SetRegion),
    AdaptPassThrough(IClientGameServerMap::SendUserConnectAndAuthenticate),
    AdaptPassThrough(IClientGameServerMap::CreateUnauthenticatedUserConnection),
    AdaptPassThrough(IClientGameServerMap::SendUserDisconnect),
    AdaptPassThrough(IClientGameServerMap::BUpdateUserData),
    AdaptPassThrough(IClientGameServerMap::GetAuthSessionTicket),
    AdaptPassThrough(IClientGameServerMap::BeginAuthSession),
    AdaptPassThrough(IClientGameServerMap::EndAuthSession),
    AdaptPassThrough(IClientGameServerMap::CancelAuthTicket),
    AdaptEmpty(IClientGameServerMap::UserHasLicenseForApp),
    AdaptPassThrough(IClientGameServerMap::RequestUserGroupStatus),
    AdaptPassThrough(IClientGameServerMap::GetGameplayStats),
    AdaptPassThrough(IClientGameServerMap::GetServerReputation),
    AdaptPassThrough(IClientGameServerMap::GetPublicIP),
    AdaptPassThrough(IClientGameServerMap::HandleIncomingPacket),
    AdaptPassThrough(IClientGameServerMap::GetNextOutgoingPacket),
    AdaptPassThrough(IClientGameServerMap::EnableHeartbeats),
    AdaptPassThrough(IClientGameServerMap::SetHeartbeatInterval),
    AdaptPassThrough(IClientGameServerMap::ForceHeartbeat),
    AdaptPassThrough(IClientGameServerMap::AssociateWithClan),
    AdaptPassThrough(IClientGameServerMap::ComputeNewPlayerCompatibility),
};
