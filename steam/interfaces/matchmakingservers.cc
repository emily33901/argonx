#include <precompiled.hh>

#include "helpers.hh"

#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
class IClientMatchmakingServers {
public:
    virtual unknown_ret RequestInternetServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *)  = 0;
    virtual unknown_ret RequestLANServerList(unsigned int, _ISteamMatchmakingServerListResponse_v001 *)                                                   = 0;
    virtual unknown_ret RequestFriendsServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *)   = 0;
    virtual unknown_ret RequestFavoritesServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) = 0;
    virtual unknown_ret RequestHistoryServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *)   = 0;
    virtual unknown_ret RequestSpectatorServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) = 0;
    virtual unknown_ret GetServerDetails(_EMatchMakingType_v001, int)                                                                                     = 0;
    virtual unknown_ret CancelQuery(_EMatchMakingType_v001)                                                                                               = 0;
    virtual unknown_ret RefreshQuery(_EMatchMakingType_v001)                                                                                              = 0;
    virtual unknown_ret IsRefreshing(_EMatchMakingType_v001)                                                                                              = 0;
    virtual unknown_ret GetServerCount(_EMatchMakingType_v001)                                                                                            = 0;
    virtual unknown_ret RefreshServer(_EMatchMakingType_v001, int)                                                                                        = 0;
    virtual unknown_ret PingServer(unsigned int, unsigned short, ISteamMatchmakingPingResponse *)                                                         = 0;
    virtual unknown_ret PlayerDetails(unsigned int, unsigned short, ISteamMatchmakingPlayersResponse *)                                                   = 0;
    virtual unknown_ret ServerRules(unsigned int, unsigned short, ISteamMatchmakingRulesResponse *)                                                       = 0;
    virtual unknown_ret CancelServerQuery(int)                                                                                                            = 0;
};
} // namespace Reference

template <bool isServer>
class ClientMatchmakingServers : public Reference::IClientMatchmakingServers {
public:
    UserHandle userHandle;
    ClientMatchmakingServers(UserHandle h) : userHandle(h) {}

    unknown_ret RequestInternetServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) override {
        return unknown_ret();
    }
    unknown_ret RequestLANServerList(unsigned int, _ISteamMatchmakingServerListResponse_v001 *) override {
        return unknown_ret();
    }
    unknown_ret RequestFriendsServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) override {
        return unknown_ret();
    }
    unknown_ret RequestFavoritesServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) override {
        return unknown_ret();
    }
    unknown_ret RequestHistoryServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) override {
        return unknown_ret();
    }
    unknown_ret RequestSpectatorServerList(unsigned int, MatchMakingKeyValuePair_t **, unsigned int, _ISteamMatchmakingServerListResponse_v001 *) override {
        return unknown_ret();
    }
    unknown_ret GetServerDetails(_EMatchMakingType_v001, int) override {
        return unknown_ret();
    }
    unknown_ret CancelQuery(_EMatchMakingType_v001) override {
        return unknown_ret();
    }
    unknown_ret RefreshQuery(_EMatchMakingType_v001) override {
        return unknown_ret();
    }
    unknown_ret IsRefreshing(_EMatchMakingType_v001) override {
        return unknown_ret();
    }
    unknown_ret GetServerCount(_EMatchMakingType_v001) override {
        return unknown_ret();
    }
    unknown_ret RefreshServer(_EMatchMakingType_v001, int) override {
        return unknown_ret();
    }
    unknown_ret PingServer(unsigned int, unsigned short, ISteamMatchmakingPingResponse *) override {
        return unknown_ret();
    }
    unknown_ret PlayerDetails(unsigned int, unsigned short, ISteamMatchmakingPlayersResponse *) override {
        return unknown_ret();
    }
    unknown_ret ServerRules(unsigned int, unsigned short, ISteamMatchmakingRulesResponse *) override {
        return unknown_ret();
    }
    unknown_ret CancelServerQuery(int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientMatchmakingServers, "SteamMatchmakingServers");

using IClientMatchmakingServers = ClientMatchmakingServers<false>;

AdaptDeclare(ISteamMatchmakingServers002);
AdaptDefine(ISteamMatchmakingServers002, IClientMatchmakingServers, "SteamMatchmakingServers002") = {
    AdaptPassThrough(IClientMatchmakingServers::RequestInternetServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestLANServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestFriendsServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestFavoritesServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestHistoryServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestSpectatorServerList),
    AdaptEmpty(IClientMatchmakingServers::ReleaseRequest),
    AdaptPassThrough(IClientMatchmakingServers::GetServerDetails),
    AdaptPassThrough(IClientMatchmakingServers::CancelQuery),
    AdaptPassThrough(IClientMatchmakingServers::RefreshQuery),
    AdaptPassThrough(IClientMatchmakingServers::IsRefreshing),
    AdaptPassThrough(IClientMatchmakingServers::GetServerCount),
    AdaptPassThrough(IClientMatchmakingServers::RefreshServer),
    AdaptPassThrough(IClientMatchmakingServers::PingServer),
    AdaptPassThrough(IClientMatchmakingServers::PlayerDetails),
    AdaptPassThrough(IClientMatchmakingServers::ServerRules),
    AdaptPassThrough(IClientMatchmakingServers::CancelServerQuery),
};
AdaptDeclare(ISteamMatchmakingServers001);
AdaptDefine(ISteamMatchmakingServers001, IClientMatchmakingServers, "SteamMatchmakingServers001") = {
    AdaptPassThrough(IClientMatchmakingServers::RequestInternetServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestLANServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestFriendsServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestFavoritesServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestHistoryServerList),
    AdaptPassThrough(IClientMatchmakingServers::RequestSpectatorServerList),
    AdaptPassThrough(IClientMatchmakingServers::GetServerDetails),
    AdaptPassThrough(IClientMatchmakingServers::CancelQuery),
    AdaptPassThrough(IClientMatchmakingServers::RefreshQuery),
    AdaptPassThrough(IClientMatchmakingServers::IsRefreshing),
    AdaptPassThrough(IClientMatchmakingServers::GetServerCount),
    AdaptPassThrough(IClientMatchmakingServers::RefreshServer),
    AdaptPassThrough(IClientMatchmakingServers::PingServer),
    AdaptPassThrough(IClientMatchmakingServers::PlayerDetails),
    AdaptPassThrough(IClientMatchmakingServers::ServerRules),
    AdaptPassThrough(IClientMatchmakingServers::CancelServerQuery),
};
