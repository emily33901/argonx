
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientVR.h"
}

template <bool isServer>
class ClientVR : public Reference::IClientVR {
public:
    UserHandle userHandle;
    ClientVR(UserHandle h) : userHandle(h) {}

    unknown_ret GetCurrentHmd() override {
        return unknown_ret();
    }
    unknown_ret GetCompositor() override {
        return unknown_ret();
    }
    unknown_ret GetOverlay() override {
        return unknown_ret();
    }
    unknown_ret GetChaperone() override {
        return unknown_ret();
    }
    unknown_ret GetSettings() override {
        return unknown_ret();
    }
    unknown_ret GetExternalEventSource() override {
        return unknown_ret();
    }
    unknown_ret GetOverlayHandle() override {
        return unknown_ret();
    }
    unknown_ret IsHmdPresent() override {
        return unknown_ret();
    }
    unknown_ret UpdateHmdStatus() override {
        return unknown_ret();
    }
    unknown_ret IsVRModeActive() override {
        return unknown_ret();
    }
    unknown_ret InitVR(bool, EClientVRError *, vr::EVRInitError *) override {
        return unknown_ret();
    }
    unknown_ret StartSteamVR(char const *) override {
        return unknown_ret();
    }
    unknown_ret CleanupVR() override {
        return unknown_ret();
    }
    unknown_ret QuitAllVR() override {
        return unknown_ret();
    }
    unknown_ret QuitApplication(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetStringForHmdError(vr::EVRInitError) override {
        return unknown_ret();
    }
    unknown_ret LaunchApplication(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetSteamVRAppId() override {
        return unknown_ret();
    }
    unknown_ret GetSteamVRPid() override {
        return unknown_ret();
    }        
    unknown_ret GetWebSecret() override {
	return unknown_ret();
    }
};

AdaptExposeClientServer(ClientVR, "SteamVR");

using IClientVR = ClientVR<false>;
