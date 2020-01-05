
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientAppDisableUpdate.h"
}

template <bool isServer>
class ClientAppDisableUpdate : public Reference::IClientAppDisableUpdate {
public:
    UserHandle userHandle;
    ClientAppDisableUpdate(UserHandle h) : userHandle(h) {}

    unknown_ret SetAppUpdateDisabledSecondsRemaining(unsigned int, unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientAppDisableUpdate, "SteamAppDisableUpdate");

using IClientAppDisableUpdate = ClientAppDisableUpdate<false>;

AdaptDeclare(ISteamAppDisableUpdate001);
AdaptDefine(ISteamAppDisableUpdate001, IClientAppDisableUpdate, "SteamAppDisableUpdate001") = {
    AdaptPassThrough(IClientAppDisableUpdate::SetAppUpdateDisabledSecondsRemaining),
};
