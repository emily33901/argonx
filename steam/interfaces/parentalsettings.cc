
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientParentalSettings.h"
}

template <bool isServer>
class ClientParentalSettings : public Reference::IClientParentalSettings {
public:
    UserHandle userHandle;
    ClientParentalSettings(UserHandle h) : userHandle(h) {}

    unknown_ret BIsParentalLockEnabled() override {
        return unknown_ret();
    }
    unknown_ret BIsParentalLockLocked() override {
        return unknown_ret();
    }
    unknown_ret BIsAppBlocked(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsAppInBlockList(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsFeatureBlocked(EParentalFeature) override {
        return unknown_ret();
    }
    unknown_ret BIsFeatureInBlockList(EParentalFeature) override {
        return unknown_ret();
    }
    unknown_ret BGetSerializedParentalSettings(CUtlBuffer *) override {
        return unknown_ret();
    }
    unknown_ret BGetRecoveryEmail(char *, int) override {
        return unknown_ret();
    }
    unknown_ret BIsLockFromSiteLicense() override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientParentalSettings, "SteamParentalSettings");

using IClientParentalSettings = ClientParentalSettings<false>;

AdaptDeclare(ISteamParentalSettings001);
AdaptDefine(ISteamParentalSettings001, IClientParentalSettings, "SteamParentalSettings001") = {
    AdaptPassThrough(IClientParentalSettings::BIsParentalLockEnabled),
    AdaptPassThrough(IClientParentalSettings::BIsParentalLockLocked),
    AdaptPassThrough(IClientParentalSettings::BIsAppBlocked),
    AdaptPassThrough(IClientParentalSettings::BIsAppInBlockList),
    AdaptPassThrough(IClientParentalSettings::BIsFeatureBlocked),
    AdaptPassThrough(IClientParentalSettings::BIsFeatureInBlockList),
};
