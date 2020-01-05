
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientParties.h"
}

template <bool isServer>
class ClientParties : public Reference::IClientParties {
public:
    UserHandle userHandle;
    ClientParties(UserHandle h) : userHandle(h) {}

    unknown_ret GetNumActiveBeacons() override {
        return unknown_ret();
    }
    unknown_ret GetBeaconByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetBeaconDetails(unsigned long long, CSteamID *, SteamPartyBeaconLocation_t *, char *, int) override {
        return unknown_ret();
    }
    unknown_ret JoinParty(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetNumAvailableBeaconLocations(unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetAvailableBeaconLocations(SteamPartyBeaconLocation_t *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CreateBeacon(unsigned int, SteamPartyBeaconLocation_t *, int, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret OnReservationCompleted(unsigned long long, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret CancelReservation(unsigned long long, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret ChangeNumOpenSlots(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret DestroyBeacon(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetBeaconLocationData(SteamPartyBeaconLocation_t, ESteamPartyBeaconLocationData, char *, int) override {
        return unknown_ret();
    }
    unknown_ret ReservePartySlot(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientParties, "SteamParties");

using IClientParties = ClientParties<false>;

AdaptDeclare(ISteamParties002);
AdaptDefine(ISteamParties002, IClientParties, "SteamParties002") = {
    AdaptPassThrough(IClientParties::GetNumActiveBeacons),
    AdaptPassThrough(IClientParties::GetBeaconByIndex),
    AdaptPassThrough(IClientParties::GetBeaconDetails),
    AdaptPassThrough(IClientParties::JoinParty),
    AdaptPassThrough(IClientParties::GetNumAvailableBeaconLocations),
    AdaptPassThrough(IClientParties::GetAvailableBeaconLocations),
    AdaptPassThrough(IClientParties::CreateBeacon),
    AdaptPassThrough(IClientParties::OnReservationCompleted),
    AdaptPassThrough(IClientParties::CancelReservation),
    AdaptPassThrough(IClientParties::ChangeNumOpenSlots),
    AdaptPassThrough(IClientParties::DestroyBeacon),
    AdaptPassThrough(IClientParties::GetBeaconLocationData),
};
AdaptDeclare(ISteamParties001);
AdaptDefine(ISteamParties001, IClientParties, "SteamParties001") = {
    AdaptPassThrough(IClientParties::GetNumActiveBeacons),
    AdaptPassThrough(IClientParties::GetBeaconByIndex),
    AdaptPassThrough(IClientParties::GetBeaconDetails),
    AdaptPassThrough(IClientParties::JoinParty),
    AdaptPassThrough(IClientParties::GetNumAvailableBeaconLocations),
    AdaptPassThrough(IClientParties::GetAvailableBeaconLocations),
    AdaptPassThrough(IClientParties::CreateBeacon),
    AdaptPassThrough(IClientParties::OnReservationCompleted),
    AdaptPassThrough(IClientParties::CancelReservation),
    AdaptPassThrough(IClientParties::ChangeNumOpenSlots),
    AdaptPassThrough(IClientParties::DestroyBeacon),
    AdaptPassThrough(IClientParties::GetBeaconLocationData),
};
