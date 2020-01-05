#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientDepotBuilder.h"
}

template <bool isServer>
class ClientDepotBuilder : public Reference::IClientDepotBuilder {
public:
    UserHandle userHandle;
    ClientDepotBuilder(UserHandle h) : userHandle(h) {}

    // Functions here please
    unknown_ret BGetDepotBuildStatus(unsigned long long, EDepotBuildStatus *, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret VerifyChunkStore(unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret DownloadDepot(unsigned int, unsigned int, unsigned long long, unsigned long long, unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret StartDepotBuild(unsigned int, unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret CommitAppBuild(unsigned int, unsigned int, unsigned int const *, unsigned long long const *, char const *, char const *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientDepotBuilder, "SteamDepotBuilder");

using IClientDepotBuilder = ClientDepotBuilder<false>;
