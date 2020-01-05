#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientUnifiedMessages.h"
}

template <bool isServer>
class ClientUnifiedMessages : public Reference::IClientUnifiedMessages {
public:
    UserHandle userHandle;
    ClientUnifiedMessages(UserHandle h) : userHandle(h) {}

    unknown_ret SendMethod(char const *, void const *, unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetMethodResponseInfo(unsigned long long, unsigned int *, EResult *) override {
        return unknown_ret();
    }
    unknown_ret GetMethodResponseData(unsigned long long, void *, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret ReleaseMethod(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret SendNotification(char const *, void const *, unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientUnifiedMessages, "SteamUnifiedMessages");

using IClientUnifiedMessages = ClientUnifiedMessages<false>;

AdaptDeclare(ISteamUnifiedMessages001);
AdaptDefine(ISteamUnifiedMessages001, IClientUnifiedMessages, "SteamUnifiedMessages001") = {
    AdaptPassThrough(IClientUnifiedMessages::SendMethod),
    AdaptPassThrough(IClientUnifiedMessages::GetMethodResponseInfo),
    AdaptPassThrough(IClientUnifiedMessages::GetMethodResponseData),
    AdaptPassThrough(IClientUnifiedMessages::ReleaseMethod),
    AdaptPassThrough(IClientUnifiedMessages::SendNotification),
};
