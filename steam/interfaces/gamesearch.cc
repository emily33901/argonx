#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientGameSearch.h"
}

template<bool isServer>
class ClientGameSearchMap : public Reference::IClientGameSearch {
public:
    ClientGameSearchMap(UserHandle h) {}

    unknown_ret AddGameSearchParams(char const*, char const*) override { return unknown_ret(); }
    unknown_ret SearchForGameWithLobby(CSteamID, int, int) override { return unknown_ret(); }
    unknown_ret SearchForGameSolo(int, int) override { return unknown_ret(); }
    unknown_ret AcceptGame() override { return unknown_ret(); }
    unknown_ret DeclineGame() override { return unknown_ret(); }
    unknown_ret RetrieveConnectionDetails(CSteamID, char*, int) override { return unknown_ret(); }
    unknown_ret EndGameSearch() override { return unknown_ret(); }
    unknown_ret SetGameHostParams(char const*, char const*) override { return unknown_ret(); }
    unknown_ret SetConnectionDetails(char const*, int) override { return unknown_ret(); }
    unknown_ret RequestPlayersForGame(int, int, int) override { return unknown_ret(); }
    unknown_ret HostConfirmGameStart(unsigned long long) override { return unknown_ret(); }
    unknown_ret CancelRequestPlayersForGame() override { return unknown_ret(); }
    unknown_ret SubmitPlayerResult(unsigned long long, CSteamID, EPlayerResult_t) override { return unknown_ret(); }
    unknown_ret EndGame(unsigned long long) override { return unknown_ret(); }
};

AdaptExposeClientServer(ClientGameSearchMap, "SteamGameSearch");

using IClientGameSearchMap = ClientGameSearchMap<false>;

AdaptDeclare(ISteamGameSearch001);
AdaptDefine(ISteamGameSearch001, IClientGameSearchMap, "SteamGameSearch001") = {
    AdaptPassThrough(IClientGameSearchMap::AddGameSearchParams),
    AdaptPassThrough(IClientGameSearchMap::SearchForGameWithLobby),
    AdaptPassThrough(IClientGameSearchMap::SearchForGameSolo),
    AdaptPassThrough(IClientGameSearchMap::AcceptGame),
    AdaptPassThrough(IClientGameSearchMap::DeclineGame),
    AdaptPassThrough(IClientGameSearchMap::RetrieveConnectionDetails),
    AdaptPassThrough(IClientGameSearchMap::EndGameSearch),
    AdaptPassThrough(IClientGameSearchMap::SetGameHostParams),
    AdaptPassThrough(IClientGameSearchMap::SetConnectionDetails),
    AdaptPassThrough(IClientGameSearchMap::RequestPlayersForGame),
    AdaptPassThrough(IClientGameSearchMap::HostConfirmGameStart),
    AdaptPassThrough(IClientGameSearchMap::CancelRequestPlayersForGame),
    AdaptPassThrough(IClientGameSearchMap::SubmitPlayerResult),
    AdaptPassThrough(IClientGameSearchMap::EndGame),
};
