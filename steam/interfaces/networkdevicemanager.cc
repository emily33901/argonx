#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientNetworkDeviceManager.h"
}

template <bool isServer>
class ClientNetworkDeviceManager : public Reference::IClientNetworkDeviceManager {
public:
    UserHandle userHandle;
    ClientNetworkDeviceManager(UserHandle h) : userHandle(h) {}

    unknown_ret IsInterfaceValid() override {
        return unknown_ret();
    }
    unknown_ret RefreshDevices() override {
        return unknown_ret();
    }
    unknown_ret EnumerateNetworkDevices(unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceType(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsCurrentDevice(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsCurrentlyConnected(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceIP4(unsigned int, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceBroadcastIP4(unsigned int, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceIPV6InterfaceIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceVendor(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceProduct(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetMacAddress(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetSubnetMaskBitCount(unsigned int, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetRouterAddressIP4(unsigned int, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetDNSResolversIP4(unsigned int, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceState(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDevicePluggedState(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret EnumerateWirelessEndpoints(unsigned int, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetConnectedWirelessEndpointSSID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetWirelessSecurityCapabilities(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetWirelessEndpointSSIDUserDisplayString(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetWirelessEndpointStrength(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsSecurityRequired(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCachedWirelessCredentials(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret DisconnectFromDevice(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetCustomIPSettings(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ConnectToDevice(unsigned int, unsigned int, char const *, char const *, unsigned int, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret IsWirelessEndpointForgettable(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ForgetWirelessEndpointAutoconnect(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsUsingDHCP(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCustomIPSettings(unsigned int, unsigned int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientNetworkDeviceManager, "SteamNetworkDeviceManager");

using IClientNetworkDeviceManager = ClientNetworkDeviceManager<false>;
