#include <precompiled.hh>

#include "helpers.hh"

#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientMatchmaking.h"
}

template <bool isServer>
class ClientMatchmakingMap : public Reference::IClientMatchmaking {
public:
    UserHandle userHandle;
    ClientMatchmakingMap(UserHandle h) : userHandle(h) {}

    // Functions here please
    unknown_ret GetFavoriteGameCount() override {
        return unknown_ret();
    }
    unknown_ret GetFavoriteGame(int, unsigned int *, unsigned int *, unsigned short *, unsigned short *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret AddFavoriteGame(unsigned int, unsigned int, unsigned short, unsigned short, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RemoveFavoriteGame(unsigned int, unsigned int, unsigned short, unsigned short, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RequestLobbyList() override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListStringFilter(char const *, char const *, ELobbyComparison) override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListNumericalFilter(char const *, int, ELobbyComparison) override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListNearValueFilter(char const *, int) override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListFilterSlotsAvailable(int) override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter) override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListResultCountFilter(int) override {
        return unknown_ret();
    }
    unknown_ret AddRequestLobbyListCompatibleMembersFilter(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyByIndex(int) override {
        return unknown_ret();
    }
    unknown_ret CreateLobby(ELobbyType, int) override {
        return unknown_ret();
    }
    unknown_ret JoinLobby(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret LeaveLobby(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret InviteUserToLobby(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetNumLobbyMembers(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyMemberByIndex(CSteamID, int) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyData(CSteamID, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyData(CSteamID, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyDataCount(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyDataByIndex(CSteamID, int, char *, int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret DeleteLobbyData(CSteamID, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyMemberData(CSteamID, CSteamID, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyMemberData(CSteamID, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SendLobbyChatMsg(CSteamID, void const *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyChatEntry(CSteamID, int, CSteamID *, void *, int, EChatEntryType *) override {
        return unknown_ret();
    }
    unknown_ret RequestLobbyData(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyGameServer(CSteamID, unsigned int, unsigned short, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyGameServer(CSteamID, unsigned int *, unsigned short *, CSteamID *) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyMemberLimit(CSteamID, int) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyMemberLimit(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyVoiceEnabled(CSteamID, bool) override {
        return unknown_ret();
    }
    unknown_ret RequestFriendsLobbies() override {
        return unknown_ret();
    }
    unknown_ret SetLobbyType(CSteamID, ELobbyType) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyJoinable(CSteamID, bool) override {
        return unknown_ret();
    }
    unknown_ret GetLobbyOwner(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret SetLobbyOwner(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret SetLinkedLobby(CSteamID, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret BeginGMSQuery(unsigned int, int, char const *) override {
        return unknown_ret();
    }
    unknown_ret PollGMSQuery(long long) override {
        return unknown_ret();
    }
    unknown_ret GetGMSQueryResults(long long, GMSQueryResult_t *, int) override {
        return unknown_ret();
    }
    unknown_ret ReleaseGMSQuery(long long) override {
        return unknown_ret();
    }
    unknown_ret EnsureFavoriteGameAccountsUpdated(bool) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientMatchmakingMap, "SteamMatchmaking");

using IClientMatchmakingMap = ClientMatchmakingMap<false>;

AdaptDeclare(ISteamMatchmaking005);
AdaptDefine(ISteamMatchmaking005, IClientMatchmakingMap, "SteamMatchmaking005") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListSlotsAvailableFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNearValueFilter),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::RequestFriendsLobbies),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyType),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyOwner),
    AdaptEmpty(IClientMatchmakingMap::GetLobbyDistance),
};

AdaptDeclare(ISteamMatchmaking004);
AdaptDefine(ISteamMatchmaking004, IClientMatchmakingMap, "SteamMatchmaking004") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListSlotsAvailableFilter),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::RequestFriendsLobbies),
};
AdaptDeclare(ISteamMatchmaking006);
AdaptDefine(ISteamMatchmaking006, IClientMatchmakingMap, "SteamMatchmaking006") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNearValueFilter),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyType),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyOwner),
};
AdaptDeclare(ISteamMatchmaking009);
AdaptDefine(ISteamMatchmaking009, IClientMatchmakingMap, "SteamMatchmaking009") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListStringFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNearValueFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListFilterSlotsAvailable),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListDistanceFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListResultCountFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListCompatibleMembersFilter),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyDataCount),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyDataByIndex),
    AdaptPassThrough(IClientMatchmakingMap::DeleteLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyType),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyJoinable),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyOwner),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyOwner),
    AdaptPassThrough(IClientMatchmakingMap::SetLinkedLobby),
};
AdaptDeclare(ISteamMatchmaking003);
AdaptDefine(ISteamMatchmaking003, IClientMatchmakingMap, "SteamMatchmaking003") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptEmpty(IClientMatchmakingMap::AddRequestLobbyListSlotsAvailableFilter),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyVoiceEnabled),
    AdaptPassThrough(IClientMatchmakingMap::RequestFriendsLobbies),
};
AdaptDeclare(ISteamMatchmaking001);
AdaptDefine(ISteamMatchmaking001, IClientMatchmakingMap, "SteamMatchmaking001") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptEmpty(IClientMatchmakingMap::GetFavoriteGame2),
    AdaptEmpty(IClientMatchmakingMap::AddFavoriteGame2),
    AdaptEmpty(IClientMatchmakingMap::RemoveFavoriteGame2),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
};
AdaptDeclare(ISteamMatchmaking002);
AdaptDefine(ISteamMatchmaking002, IClientMatchmakingMap, "SteamMatchmaking002") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
};
AdaptDeclare(ISteamMatchmaking007);
AdaptDefine(ISteamMatchmaking007, IClientMatchmakingMap, "SteamMatchmaking007") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListStringFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNearValueFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListFilterSlotsAvailable),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyDataCount),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyDataByIndex),
    AdaptPassThrough(IClientMatchmakingMap::DeleteLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyType),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyJoinable),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyOwner),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyOwner),
};
AdaptDeclare(ISteamMatchmaking008);
AdaptDefine(ISteamMatchmaking008, IClientMatchmakingMap, "SteamMatchmaking008") = {
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGameCount),
    AdaptPassThrough(IClientMatchmakingMap::GetFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::AddFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RemoveFavoriteGame),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyList),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListStringFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNumericalFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListNearValueFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListFilterSlotsAvailable),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListDistanceFilter),
    AdaptPassThrough(IClientMatchmakingMap::AddRequestLobbyListResultCountFilter),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyByIndex),
    AdaptPassThrough(IClientMatchmakingMap::CreateLobby),
    AdaptPassThrough(IClientMatchmakingMap::JoinLobby),
    AdaptPassThrough(IClientMatchmakingMap::LeaveLobby),
    AdaptPassThrough(IClientMatchmakingMap::InviteUserToLobby),
    AdaptPassThrough(IClientMatchmakingMap::GetNumLobbyMembers),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberByIndex),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyDataCount),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyDataByIndex),
    AdaptPassThrough(IClientMatchmakingMap::DeleteLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberData),
    AdaptPassThrough(IClientMatchmakingMap::SendLobbyChatMsg),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyChatEntry),
    AdaptPassThrough(IClientMatchmakingMap::RequestLobbyData),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyGameServer),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyMemberLimit),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyType),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyJoinable),
    AdaptPassThrough(IClientMatchmakingMap::GetLobbyOwner),
    AdaptPassThrough(IClientMatchmakingMap::SetLobbyOwner),
};