
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientStreamLauncher.h"
}

template <bool isServer>
class ClientStreamLauncher : public Reference::IClientStreamLauncher {
public:
    UserHandle userHandle;
    ClientStreamLauncher(UserHandle h) : userHandle(h) {}

    unknown_ret StartStreaming(char const *) override {
        return unknown_ret();
    }
    unknown_ret StopStreaming() override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientStreamLauncher, "SteamStreamLauncher");

using IClientStreamLauncher = ClientStreamLauncher<false>;

AdaptDeclare(ISteamStreamLauncher001);
AdaptDefine(ISteamStreamLauncher001, IClientStreamLauncher, "SteamStreamLauncher001") = {
    AdaptPassThrough(IClientStreamLauncher::StartStreaming),
    AdaptPassThrough(IClientStreamLauncher::StopStreaming),
};
