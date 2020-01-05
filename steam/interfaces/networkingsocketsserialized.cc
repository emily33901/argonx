
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientNetworkingSocketsSerialized.h"
}

template <bool isServer>
class ClientNetworkingSocketsSerialized : public Reference::IClientNetworkingSocketsSerialized {
public:
    UserHandle userHandle;
    ClientNetworkingSocketsSerialized(UserHandle h) : userHandle(h) {}

    unknown_ret SendP2PRendezvous(CSteamID, unsigned int, void const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SendP2PConnectionFailure(CSteamID, unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetCertAsync() override {
        return unknown_ret();
    }
    unknown_ret CacheRelayTicket(void const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCachedRelayTicketCount() override {
        return unknown_ret();
    }
    unknown_ret GetCachedRelayTicket(unsigned int, void *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret PostConnectionStateMsg(void const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret TEST_ClearInMemoryCachedCredentials() override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientNetworkingSocketsSerialized, "SteamNetworkingSocketsSerialized");

using IClientNetworkingSocketsSerialized = ClientNetworkingSocketsSerialized<false>;
