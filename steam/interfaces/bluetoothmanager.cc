
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientBluetoothManager.h"
}

template <bool isServer>
class ClientBluetoothManager : public Reference::IClientBluetoothManager {
public:
    UserHandle userHandle;
    ClientBluetoothManager(UserHandle h) : userHandle(h) {}

    unknown_ret SetDiscovering(bool) override {
        return unknown_ret();
    }
    unknown_ret EnumerateDevice(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceType(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetDeviceName(char const *) override {
        return unknown_ret();
    }
    unknown_ret IsConnected(char const *) override {
        return unknown_ret();
    }
    unknown_ret IsPaired(char const *) override {
        return unknown_ret();
    }
    unknown_ret Pair(char const *) override {
        return unknown_ret();
    }
    unknown_ret UnPair(char const *) override {
        return unknown_ret();
    }
    unknown_ret Connect(char const *) override {
        return unknown_ret();
    }
    unknown_ret Disconnect(char const *) override {
        return unknown_ret();
    }
    unknown_ret IsAvailable() override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientBluetoothManager, "SteamBluetoothManager");

using IClientBluetoothManager = ClientBluetoothManager<false>;
