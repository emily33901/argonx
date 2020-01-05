
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientSharedConnection.h"
}

template <bool isServer>
class ClientSharedConnection : public Reference::IClientSharedConnection {
public:
    UserHandle userHandle;
    ClientSharedConnection(UserHandle h) : userHandle(h) {}

    unknown_ret AllocateSharedConnection() override {
        return unknown_ret();
    }
    unknown_ret ReleaseSharedConnection(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SendMessage(unsigned int, void const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SendMessageAndAwaitResponse(unsigned int, void const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RegisterEMsgHandler(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RegisterServiceMethodHandler(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret BPopReceivedMessage(unsigned int, CUtlBuffer *, unsigned int *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientSharedConnection, "SteamSharedConnection");

using IClientSharedConnection = ClientSharedConnection<false>;
