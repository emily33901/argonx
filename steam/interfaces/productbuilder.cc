#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientProductBuilder.h"
}


template<bool isServer>
class ClientProductBuilder : public Reference::IClientProductBuilder {
public:
    UserHandle userHandle;
    ClientProductBuilder(UserHandle h) : userHandle(h) {}

    virtual unknown_ret SignInstallScript(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }        
    virtual unknown_ret DRMWrap(unsigned int, char const*, char const*, char const*, unsigned int) override {
	return unknown_ret();
    }
    virtual unknown_ret CEGWrap(unsigned int, char const*, char const*, char const*) override {
	return unknown_ret();
    }

};

AdaptExposeClientServer(ClientProductBuilder, "SteamProductBuilder");

using IClientProductBuilder = ClientProductBuilder<false>;


