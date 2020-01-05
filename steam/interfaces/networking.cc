#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientNetworking.h"
}

template <bool isServer>
class ClientNetworkingMap : public Reference::IClientNetworking {
public:
    UserHandle userHandle;
    ClientNetworkingMap(UserHandle h) : userHandle(h) {}

    unknown_ret SendP2PPacket(CSteamID, void const*, unsigned int, EP2PSend, int) override {
        return unknown_ret();
    }
    unknown_ret IsP2PPacketAvailable(unsigned int*, int) override {
        return unknown_ret();
    }
    unknown_ret ReadP2PPacket(void*, unsigned int, unsigned int*, CSteamID*, int) override {
        return unknown_ret();
    }
    unknown_ret AcceptP2PSessionWithUser(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret CloseP2PSessionWithUser(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret CloseP2PChannelWithUser(CSteamID, int) override {
        return unknown_ret();
    }
    unknown_ret GetP2PSessionState(CSteamID, P2PSessionState_t*) override {
        return unknown_ret();
    }
    unknown_ret AllowP2PPacketRelay(bool) override {
        return unknown_ret();
    }
    unknown_ret CreateListenSocket(int, SteamIPAddress_t, unsigned short, bool) override {
        return unknown_ret();
    }
    unknown_ret CreateP2PConnectionSocket(CSteamID, int, int, bool) override {
        return unknown_ret();
    }
    unknown_ret CreateConnectionSocket(SteamIPAddress_t, unsigned short, int) override {
        return unknown_ret();
    }
    unknown_ret DestroySocket(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret DestroyListenSocket(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SendDataOnSocket(unsigned int, void*, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret IsDataAvailableOnSocket(unsigned int, unsigned int*) override {
        return unknown_ret();
    }
    unknown_ret RetrieveDataFromSocket(unsigned int, void*, unsigned int, unsigned int*) override {
        return unknown_ret();
    }
    unknown_ret IsDataAvailable(unsigned int, unsigned int*, unsigned int*) override {
        return unknown_ret();
    }
    unknown_ret RetrieveData(unsigned int, void*, unsigned int, unsigned int*, unsigned int*) override {
        return unknown_ret();
    }
    unknown_ret GetSocketInfo(unsigned int, CSteamID*, int*, SteamIPAddress_t*, unsigned short*) override {
        return unknown_ret();
    }
    unknown_ret GetListenSocketInfo(unsigned int, SteamIPAddress_t*, unsigned short*) override {
        return unknown_ret();
    }
    unknown_ret GetSocketConnectionType(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetMaxPacketSize(unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientNetworkingMap, "SteamNetworking");

using IClientNetworking = ClientNetworkingMap<false>;

AdaptDeclare(ISteamNetworking002);
AdaptDefine(ISteamNetworking002, IClientNetworking, "SteamNetworking002") = {
    AdaptPassThrough(IClientNetworking::CreateListenSocket),
    AdaptPassThrough(IClientNetworking::CreateP2PConnectionSocket),
    AdaptPassThrough(IClientNetworking::CreateConnectionSocket),
    AdaptPassThrough(IClientNetworking::DestroySocket),
    AdaptPassThrough(IClientNetworking::DestroyListenSocket),
    AdaptPassThrough(IClientNetworking::SendDataOnSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailableOnSocket),
    AdaptPassThrough(IClientNetworking::RetrieveDataFromSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailable),
    AdaptPassThrough(IClientNetworking::RetrieveData),
    AdaptPassThrough(IClientNetworking::GetSocketInfo),
    AdaptPassThrough(IClientNetworking::GetListenSocketInfo),
    AdaptPassThrough(IClientNetworking::GetSocketConnectionType),
    AdaptPassThrough(IClientNetworking::GetMaxPacketSize),
};

AdaptDeclare(ISteamNetworking004);
AdaptDefine(ISteamNetworking004, IClientNetworking, "SteamNetworking004") = {
    AdaptPassThrough(IClientNetworking::SendP2PPacket),
    AdaptPassThrough(IClientNetworking::IsP2PPacketAvailable),
    AdaptPassThrough(IClientNetworking::ReadP2PPacket),
    AdaptPassThrough(IClientNetworking::AcceptP2PSessionWithUser),
    AdaptPassThrough(IClientNetworking::CloseP2PSessionWithUser),
    AdaptPassThrough(IClientNetworking::GetP2PSessionState),
    AdaptPassThrough(IClientNetworking::CreateListenSocket),
    AdaptPassThrough(IClientNetworking::CreateP2PConnectionSocket),
    AdaptPassThrough(IClientNetworking::CreateConnectionSocket),
    AdaptPassThrough(IClientNetworking::DestroySocket),
    AdaptPassThrough(IClientNetworking::DestroyListenSocket),
    AdaptPassThrough(IClientNetworking::SendDataOnSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailableOnSocket),
    AdaptPassThrough(IClientNetworking::RetrieveDataFromSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailable),
    AdaptPassThrough(IClientNetworking::RetrieveData),
    AdaptPassThrough(IClientNetworking::GetSocketInfo),
    AdaptPassThrough(IClientNetworking::GetListenSocketInfo),
    AdaptPassThrough(IClientNetworking::GetSocketConnectionType),
    AdaptPassThrough(IClientNetworking::GetMaxPacketSize),
};
AdaptDeclare(ISteamNetworking005);
AdaptDefine(ISteamNetworking005, IClientNetworking, "SteamNetworking005") = {
    AdaptPassThrough(IClientNetworking::SendP2PPacket),
    AdaptPassThrough(IClientNetworking::IsP2PPacketAvailable),
    AdaptPassThrough(IClientNetworking::ReadP2PPacket),
    AdaptPassThrough(IClientNetworking::AcceptP2PSessionWithUser),
    AdaptPassThrough(IClientNetworking::CloseP2PSessionWithUser),
    AdaptPassThrough(IClientNetworking::CloseP2PChannelWithUser),
    AdaptPassThrough(IClientNetworking::GetP2PSessionState),
    AdaptPassThrough(IClientNetworking::AllowP2PPacketRelay),
    AdaptPassThrough(IClientNetworking::CreateListenSocket),
    AdaptPassThrough(IClientNetworking::CreateP2PConnectionSocket),
    AdaptPassThrough(IClientNetworking::CreateConnectionSocket),
    AdaptPassThrough(IClientNetworking::DestroySocket),
    AdaptPassThrough(IClientNetworking::DestroyListenSocket),
    AdaptPassThrough(IClientNetworking::SendDataOnSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailableOnSocket),
    AdaptPassThrough(IClientNetworking::RetrieveDataFromSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailable),
    AdaptPassThrough(IClientNetworking::RetrieveData),
    AdaptPassThrough(IClientNetworking::GetSocketInfo),
    AdaptPassThrough(IClientNetworking::GetListenSocketInfo),
    AdaptPassThrough(IClientNetworking::GetSocketConnectionType),
    AdaptPassThrough(IClientNetworking::GetMaxPacketSize),
};
AdaptDeclare(ISteamNetworking001);
AdaptDefine(ISteamNetworking001, IClientNetworking, "SteamNetworking001") = {
    AdaptPassThrough(IClientNetworking::CreateListenSocket),
    AdaptPassThrough(IClientNetworking::CreateP2PConnectionSocket),
    AdaptPassThrough(IClientNetworking::CreateConnectionSocket),
    AdaptPassThrough(IClientNetworking::DestroySocket),
    AdaptPassThrough(IClientNetworking::DestroyListenSocket),
    AdaptPassThrough(IClientNetworking::SendDataOnSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailableOnSocket),
    AdaptPassThrough(IClientNetworking::RetrieveDataFromSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailable),
    AdaptPassThrough(IClientNetworking::RetrieveData),
    AdaptPassThrough(IClientNetworking::GetSocketInfo),
    AdaptPassThrough(IClientNetworking::GetListenSocketInfo),
};
AdaptDeclare(ISteamNetworking003);
AdaptDefine(ISteamNetworking003, IClientNetworking, "SteamNetworking003") = {
    AdaptPassThrough(IClientNetworking::SendP2PPacket),
    AdaptPassThrough(IClientNetworking::IsP2PPacketAvailable),
    AdaptPassThrough(IClientNetworking::ReadP2PPacket),
    AdaptPassThrough(IClientNetworking::AcceptP2PSessionWithUser),
    AdaptPassThrough(IClientNetworking::CloseP2PSessionWithUser),
    AdaptPassThrough(IClientNetworking::GetP2PSessionState),
    AdaptPassThrough(IClientNetworking::CreateListenSocket),
    AdaptPassThrough(IClientNetworking::CreateP2PConnectionSocket),
    AdaptPassThrough(IClientNetworking::CreateConnectionSocket),
    AdaptPassThrough(IClientNetworking::DestroySocket),
    AdaptPassThrough(IClientNetworking::DestroyListenSocket),
    AdaptPassThrough(IClientNetworking::SendDataOnSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailableOnSocket),
    AdaptPassThrough(IClientNetworking::RetrieveDataFromSocket),
    AdaptPassThrough(IClientNetworking::IsDataAvailable),
    AdaptPassThrough(IClientNetworking::RetrieveData),
    AdaptPassThrough(IClientNetworking::GetSocketInfo),
    AdaptPassThrough(IClientNetworking::GetListenSocketInfo),
    AdaptPassThrough(IClientNetworking::GetSocketConnectionType),
    AdaptPassThrough(IClientNetworking::GetMaxPacketSize),
};
