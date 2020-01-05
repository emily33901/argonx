
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientGameNotifications.h"
}

template <bool isServer>
class ClientGameNotifications : public Reference::IClientGameNotifications {
public:
    UserHandle userHandle;
    ClientGameNotifications(UserHandle h) : userHandle(h) {}

    unknown_ret EnumerateNotifications(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetNotificationCount(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetNotification(unsigned int, int, GameNotification_t *) override {
        return unknown_ret();
    }
    unknown_ret RemoveSession(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret UpdateSession(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientGameNotifications, "SteamGameNotifications");

using IClientGameNotifications = ClientGameNotifications<false>;
