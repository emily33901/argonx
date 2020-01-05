#include <precompiled.hh>

#include <atomic>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientBilling.h"
}

template<bool isServer>
class ClientBillingMap : public Reference::IClientBilling {
    Steam::UserHandle userHandle;
public:

    ClientBillingMap(Steam::UserHandle h) : userHandle(h) {
    }

    unknown_ret PurchaseWithActivationCode(char const*) override { 
        return unknown_ret(); 
    }
    unknown_ret HasActiveLicense(unsigned int) override { 
        return unknown_ret(); 
    }
    unknown_ret GetLicenseInfo(unsigned int, unsigned int*, unsigned int*, int*, int*, Steam::EPaymentMethod*, unsigned int*, int*, char*) override { 
        return unknown_ret(); 
    }
    unknown_ret EnableTestLicense(unsigned int) override { 
        return unknown_ret(); 
    }
    unknown_ret DisableTestLicense(unsigned int) override { 
        return unknown_ret(); 
    }
    unknown_ret GetAppsInPackage(unsigned int, unsigned int*, unsigned int) override { 
        return unknown_ret(); 
    }
    unknown_ret RequestFreeLicenseForApps(unsigned int const*, unsigned int) override { 
        return unknown_ret(); 
    }
};

AdaptExposeClientServer(ClientBillingMap, "SteamBilling");
