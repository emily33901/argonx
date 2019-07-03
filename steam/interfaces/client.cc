#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientEngine.h"
}

const char *                                                baseAddress = "tcp://127.0.0.1:33901";
std::unordered_map<Steam::UserHandle, UserInterfaceStorage> userStorage;

// Only used on the server
Steam::UserHandle lastUserHandle = 0;

UserInterfaceStorage Steam::CreateUserInterfaceStorage() {
    auto r = (UserInterfaceStorage) new void *[(u32)Steam::InterfaceTarget::max];

    memset(r, 0, sizeof(void *) * (u32)Steam::InterfaceTarget::max);

    return r;
}

void *Steam::GetUserInterface(Steam::UserHandle h, InterfaceTarget t) {
    auto i = userStorage.find(h);
    if (i != userStorage.end()) {
        return i->second[(u32)t];
    }

    return nullptr;
}

// Wrapper for some old functionality
// This returns the interface names that will be used for each
// interface target.
// Result should be used and not stored (unless copied)
const char *InterfaceVersion(InterfaceTarget t, bool isServer) {
    auto base = InterfaceName(t);
    if (!isServer) {
        return base;
    }
    static char buf[256] = "";
    memset((void *)buf, 0, sizeof(buf));

    snprintf(buf, 255, "%sServer", base);

    return buf;
}

template <bool isServer>
class ClientEngineMap : Reference::IClientEngine {
public:
    // Inherited via IClientEngine
    virtual Steam::PipeHandle CreateSteamPipe() override {
        // TODO: we probably shouldnt create a pipe until this function gets called!
        return 1;
    }
    virtual bool BReleaseSteamPipe(Steam::PipeHandle pipe) override {
        // TODO: tell the server to release the port!
        return true;
    }
    virtual Steam::UserHandle CreateGlobalUser(Steam::PipeHandle *pipe) override {
        // TODO: This cannot be a no-op
        return 1;
    }
    virtual Steam::UserHandle ConnectToGlobalUser(Steam::PipeHandle pipe) override {
        // TODO: This cannot be a no-op!
        return 1;
    }
    virtual Steam::UserHandle CreateLocalUser(Steam::PipeHandle *pipe, EAccountType t) override {
        // TODO: this should probably hold onto the account type aswell...

        // Helper function to create a filled user interface storage
        auto fillUserInterfaceStorage = [](Steam::UserHandle h) {
            auto storage = CreateUserInterfaceStorage();
            for (u32 i = 0; i < (u32)InterfaceTarget::max; i++) {
                int err    = 0;
                storage[i] = CreateInterfaceWithEither(InterfaceVersion((InterfaceTarget)i, isServer), h);

                AssertAlways(err == 0 && storage[i] != nullptr, "CreateInterface for target %s failed! (err = %d)", InterfaceVersion((InterfaceTarget)i, isServer), err);
            }

            return storage;
        };

        auto handle = [this, &pipe, &t, &fillUserInterfaceStorage]() {
            RpcMakeCallIfClientNoUser(CreateLocalUser, engine, pipe, t) {
                lastUserHandle += 1;

                userStorage.insert({lastUserHandle, fillUserInterfaceStorage(lastUserHandle)});

                return lastUserHandle;
            };
        }();

        RpcRunOnClient() {
            // TODO: we also need to actually instantiate all of these interfaces
            // so that we can start recieving callbacks immediately.
            // (and actually return them when users ask for them)

            userStorage.insert({handle, fillUserInterfaceStorage(handle)});
        }

        return handle;
    }
    virtual void CreatePipeToLocalUser(Steam::UserHandle h, Steam::PipeHandle *pipe) override {
        // TODO: create user storage here
        *pipe = 1;
    }
    virtual void ReleaseUser(Steam::PipeHandle pipe, Steam::UserHandle h) override {
        RpcRunOnBothNoUser(ReleaseUser, engine, pipe, h) {
            if (userStorage.find(h) != userStorage.end()) {
                Defer(userStorage.erase(h));

                auto s = userStorage[h];

                for (auto i = 0; i < (u32)InterfaceTarget::max; i++) {
                    delete s[i];
                }

                delete s;
            }
        }
    }
    virtual bool IsValidHSteamUserPipe(Steam::PipeHandle pipe, Steam::UserHandle h) override {
        auto serverResult = [this, &pipe, &h]() {
            RpcMakeCallIfClientNoUser(IsValidHSteamUserPipe, engine, pipe, h) {
                return userStorage.find(h) != userStorage.end();
            }
        }();

        RpcRunOnClient() {
            return serverResult && userStorage.find(h) != userStorage.end();
        }

        return serverResult;
    }
    virtual void *GetIClientUser(Steam::UserHandle h, Steam::PipeHandle p) override {
        if (IsValidHSteamUserPipe(p, h)) {
            return Steam::GetUserInterface(h, InterfaceTarget::user);
        }
        return nullptr;
    }
    virtual void *GetIClientGameServer(Steam::UserHandle, Steam::PipeHandle) override {
        return nullptr;
    }
    virtual unknown_ret SetLocalIPBinding(unsigned int, unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUniverseName(EUniverse) override {
        return unknown_ret();
    }
    virtual void *GetIClientFriends(Steam::UserHandle h, Steam::PipeHandle p) override {
        if (IsValidHSteamUserPipe(p, h)) {
            return Steam::GetUserInterface(h, InterfaceTarget::friends);
        }
        return nullptr;
    }
    virtual unknown_ret GetIClientUtils(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientBilling(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientMatchmaking(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientApps(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientMatchmakingServers(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientGameSearch(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret RunFrame() override {
        return unknown_ret();
    }
    virtual unknown_ret GetIPCCallCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientUserStats(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientGameServerStats(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientNetworking(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientRemoteStorage(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientScreenshots(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetWarningMessageHook(void (*)(int, char const *)) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientGameCoordinator(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayNotificationPosition(ENotificationPosition) override {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayNotificationInset(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret HookScreenshots(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IsScreenshotsHooked() override {
        return unknown_ret();
    }
    virtual unknown_ret IsOverlayEnabled() override {
        return unknown_ret();
    }
    virtual unknown_ret GetAPICallResult(int, unsigned long long, void *, int, int, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientProductBuilder(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientDepotBuilder(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientNetworkDeviceManager(int) override {
        return unknown_ret();
    }
    virtual unknown_ret ConCommandInit(IConCommandBaseAccessor *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientAppManager(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientConfigStore(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret BOverlayNeedsPresent() override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientGameStats(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientHTTP(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret BShutdownIfAllPipesClosed() override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientAudio(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientMusic(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientUnifiedMessages(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientController(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientParentalSettings(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientStreamLauncher(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientDeviceAuth(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientRemoteClientManager(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientStreamClient(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientShortcuts(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientUGC(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientInventory(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientVR(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientGameNotifications(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientHTMLSurface(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientVideo(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientControllerSerialized(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientAppDisableUpdate(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret Set_Client_API_CCheckCallbackRegisteredInProcess(unsigned int (*)(int)) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientBluetoothManager(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientSharedConnection(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientShader(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientNetworkingSocketsSerialized(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientCompat(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetClientCommandLine(int, char **) override {
        return unknown_ret();
    }
    virtual unknown_ret GetIClientParties(int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret __Destructor1() override {
        return unknown_ret();
    }
#ifdef ARGONX_UNIX
    virtual unknown_ret __Destructor2() override {
        return unknown_ret();
    }
#endif
    virtual unknown_ret GetIPCServerMap() override {
        return unknown_ret();
    }
    virtual unknown_ret OnDebugTextArrived(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret OnThreadLocalRegistration() override {
        return unknown_ret();
    }
    virtual unknown_ret OnThreadBuffersOverLimit() override {
        return unknown_ret();
    }
};

AdaptExposeClientServerNoUser(ClientEngineMap, "ClientEngine");

template <bool isServer>
class SteamClientMap {
public:
    SteamClientMap(Steam::UserHandle h) {}
    SteamClientMap() {}

    virtual unknown_ret CreateSteamPipe() {
        return unknown_ret();
    }
    virtual unknown_ret BReleaseSteamPipe(int) {
        return unknown_ret();
    }
    virtual unknown_ret CreateGlobalUser(int *) {
        return unknown_ret();
    }
    virtual unknown_ret ConnectToGlobalUser(int) {
        return unknown_ret();
    }
    virtual unknown_ret CreateLocalUser(int *, EAccountType) {
        return unknown_ret();
    }
    virtual unknown_ret CreatePipeToLocalUser(int, int *) {
        return unknown_ret();
    }
    virtual unknown_ret ReleaseUser(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret IsValidHSteamUserPipe(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamUser(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamGameServer(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret SetLocalIPBinding(unsigned int, unsigned short) {
        return unknown_ret();
    }
    virtual unknown_ret GetUniverseName(EUniverse) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamFriends(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamUtils(int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamBilling(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamMatchmaking(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamApps(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamMatchmakingServers(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamGameSearch(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret RunFrame() {
        return unknown_ret();
    }
    virtual unknown_ret GetIPCCallCount() {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamUserStats(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamGameServerStats(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamNetworking(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamRemoteStorage(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamScreenshots(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret SetWarningMessageHook(void (*)(int, char const *)) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamGameCoordinator(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayNotificationPosition(ENotificationPosition) {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayNotificationInset(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret HookScreenshots(bool) {
        return unknown_ret();
    }
    virtual unknown_ret IsScreenshotsHooked() {
        return unknown_ret();
    }
    virtual unknown_ret IsOverlayEnabled() {
        return unknown_ret();
    }
    virtual unknown_ret GetAPICallResult(int, unsigned long long, void *, int, int, bool *) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamProductBuilder(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamDepotBuilder(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamNetworkDeviceManager(int) {
        return unknown_ret();
    }
    virtual unknown_ret ConCommandInit(IConCommandBaseAccessor *) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamAppManager(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamConfigStore(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret BOverlayNeedsPresent() {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamGameStats(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamHTTP(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret BShutdownIfAllPipesClosed() {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamAudio(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamMusic(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamUnifiedMessages(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamController(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamParentalSettings(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamStreamLauncher(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamDeviceAuth(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamRemoteClientManager(int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamStreamClient(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamShortcuts(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamUGC(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamInventory(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamVR(int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamGameNotifications(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamHTMLSurface(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamVideo(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamControllerSerialized(int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamAppDisableUpdate(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret Set_Client_API_CCheckCallbackRegisteredInProcess(unsigned int (*)(int)) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamBluetoothManager(int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamSharedConnection(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamShader(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamNetworkingSocketsSerialized(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamCompat(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret SetClientCommandLine(int, char **) {
        return unknown_ret();
    }
    virtual unknown_ret GetISteamParties(int, int) {
        return unknown_ret();
    }
    virtual unknown_ret __Destructor1() {
        return unknown_ret();
    }
    virtual unknown_ret GetIPCServerMap() {
        return unknown_ret();
    }
    virtual unknown_ret OnDebugTextArrived(char const *) {
        return unknown_ret();
    }
    virtual unknown_ret OnThreadLocalRegistration() {
        return unknown_ret();
    }
    virtual unknown_ret OnThreadBuffersOverLimit() {
        return unknown_ret();
    }

    // Others
    virtual unknown_ret GetIVAC(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret GetISteamContentServer(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret GetISteamMasterServerUpdater(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret GetISteamGenericInterface(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret GetISteamAppList(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret GetISteamMusicRemote(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret GetISteamInput(int, int) {
        return unknown_ret();
    }

    virtual unknown_ret Set_SteamAPI_CCheckCallbackRegisteredInProcess(int) {
        return unknown_ret();
    }
};

AdaptExposeClientServerNoUser(SteamClientMap, "SteamClient");

using ISteamClientMap = SteamClientMap<false>;

AdaptDeclare(ISteamClient006);
AdaptDefine(ISteamClient006, ISteamClientMap, "SteamClient006") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::CreateGlobalUser),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptEmpty(ISteamClientMap::GetIVAC),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetUniverseName),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamBilling),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamContentServer),
    AdaptPassThrough(ISteamClientMap::GetISteamMasterServerUpdater),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
};
AdaptExposeNoUser(ISteamClient006, ISteamClientMap, "SteamClient006");

AdaptDeclare(ISteamClient007);
AdaptDefine(ISteamClient007, ISteamClientMap, "SteamClient007") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamContentServer),
    AdaptPassThrough(ISteamClientMap::GetISteamMasterServerUpdater),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
};
AdaptExposeNoUser(ISteamClient007, ISteamClientMap, "SteamClient007");

AdaptDeclare(ISteamClient008);
AdaptDefine(ISteamClient008, ISteamClientMap, "SteamClient008") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMasterServerUpdater),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
};
AdaptExposeNoUser(ISteamClient008, ISteamClientMap, "SteamClient008");

AdaptDeclare(ISteamClient009);
AdaptDefine(ISteamClient009, ISteamClientMap, "SteamClient009") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMasterServerUpdater),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
};
AdaptExposeNoUser(ISteamClient009, ISteamClientMap, "SteamClient009");

AdaptDeclare(ISteamClient010);
AdaptDefine(ISteamClient010, ISteamClientMap, "SteamClient010") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMasterServerUpdater),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
};
AdaptExposeNoUser(ISteamClient010, ISteamClientMap, "SteamClient010");

AdaptDeclare(ISteamClient011);
AdaptDefine(ISteamClient011, ISteamClientMap, "SteamClient011") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMasterServerUpdater),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
};
AdaptExposeNoUser(ISteamClient011, ISteamClientMap, "SteamClient011");

AdaptDeclare(ISteamClient012);
AdaptDefine(ISteamClient012, ISteamClientMap, "SteamClient012") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptPassThrough(ISteamClientMap::GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
};
AdaptExposeNoUser(ISteamClient012, ISteamClientMap, "SteamClient012");

AdaptDeclare(ISteamClient013);
AdaptDefine(ISteamClient013, ISteamClientMap, "SteamClient013") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptPassThrough(ISteamClientMap::GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamInventory),
    AdaptPassThrough(ISteamClientMap::GetISteamVideo),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
};
AdaptExposeNoUser(ISteamClient013, ISteamClientMap, "SteamClient013");

AdaptDeclare(ISteamClient014);
AdaptDefine(ISteamClient014, ISteamClientMap, "SteamClient014") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptPassThrough(ISteamClientMap::GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
    AdaptPassThrough(ISteamClientMap::GetISteamMusic),
};
AdaptExposeNoUser(ISteamClient014, ISteamClientMap, "SteamClient014");

AdaptDeclare(ISteamClient015);
AdaptDefine(ISteamClient015, ISteamClientMap, "SteamClient015") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptPassThrough(ISteamClientMap::GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
    AdaptPassThrough(ISteamClientMap::GetISteamMusic),
    AdaptPassThrough(ISteamClientMap::GetISteamMusicRemote),
};
AdaptExposeNoUser(ISteamClient015, ISteamClientMap, "SteamClient015");

AdaptDeclare(ISteamClient016);
AdaptDefine(ISteamClient016, ISteamClientMap, "SteamClient016") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptPassThrough(ISteamClientMap::GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
    AdaptPassThrough(ISteamClientMap::GetISteamMusic),
    AdaptPassThrough(ISteamClientMap::GetISteamMusicRemote),
    AdaptPassThrough(ISteamClientMap::GetISteamHTMLSurface),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess),
    AdaptPassThrough(ISteamClientMap::Set_SteamAPI_CCheckCallbackRegisteredInProcess),
};
AdaptExposeNoUser(ISteamClient016, ISteamClientMap, "SteamClient016");

AdaptDeclare(ISteamClient017);
AdaptDefine(ISteamClient017, ISteamClientMap, "SteamClient017") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptEmpty(ISteamClientMap::DEPRECATED_GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
    AdaptPassThrough(ISteamClientMap::GetISteamMusic),
    AdaptPassThrough(ISteamClientMap::GetISteamMusicRemote),
    AdaptPassThrough(ISteamClientMap::GetISteamHTMLSurface),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess),
    AdaptPassThrough(ISteamClientMap::Set_SteamAPI_CCheckCallbackRegisteredInProcess),
    AdaptPassThrough(ISteamClientMap::GetISteamInventory),
    AdaptPassThrough(ISteamClientMap::GetISteamVideo),
    AdaptPassThrough(ISteamClientMap::GetISteamParentalSettings),
};
AdaptExposeNoUser(ISteamClient017, ISteamClientMap, "SteamClient017");

AdaptDeclare(ISteamClient018);
AdaptDefine(ISteamClient018, ISteamClientMap, "SteamClient018") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::GetISteamGameSearch),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptEmpty(ISteamClientMap::DEPRECATED_GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
    AdaptPassThrough(ISteamClientMap::GetISteamMusic),
    AdaptPassThrough(ISteamClientMap::GetISteamMusicRemote),
    AdaptPassThrough(ISteamClientMap::GetISteamHTMLSurface),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess),
    AdaptPassThrough(ISteamClientMap::Set_SteamAPI_CCheckCallbackRegisteredInProcess),
    AdaptPassThrough(ISteamClientMap::GetISteamInventory),
    AdaptPassThrough(ISteamClientMap::GetISteamVideo),
    AdaptPassThrough(ISteamClientMap::GetISteamParentalSettings),
    AdaptPassThrough(ISteamClientMap::GetISteamInput),
    AdaptPassThrough(ISteamClientMap::GetISteamParties),
};
AdaptExposeNoUser(ISteamClient018, ISteamClientMap, "SteamClient018");

AdaptDeclare(ISteamClient019);
AdaptDefine(ISteamClient019, ISteamClientMap, "SteamClient019") = {
    AdaptPassThrough(ISteamClientMap::CreateSteamPipe),
    AdaptPassThrough(ISteamClientMap::BReleaseSteamPipe),
    AdaptPassThrough(ISteamClientMap::ConnectToGlobalUser),
    AdaptPassThrough(ISteamClientMap::CreateLocalUser),
    AdaptPassThrough(ISteamClientMap::ReleaseUser),
    AdaptPassThrough(ISteamClientMap::GetISteamUser),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServer),
    AdaptPassThrough(ISteamClientMap::SetLocalIPBinding),
    AdaptPassThrough(ISteamClientMap::GetISteamFriends),
    AdaptPassThrough(ISteamClientMap::GetISteamUtils),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmaking),
    AdaptPassThrough(ISteamClientMap::GetISteamMatchmakingServers),
    AdaptPassThrough(ISteamClientMap::GetISteamGenericInterface),
    AdaptPassThrough(ISteamClientMap::GetISteamUserStats),
    AdaptPassThrough(ISteamClientMap::GetISteamGameServerStats),
    AdaptPassThrough(ISteamClientMap::GetISteamApps),
    AdaptPassThrough(ISteamClientMap::GetISteamNetworking),
    AdaptPassThrough(ISteamClientMap::GetISteamRemoteStorage),
    AdaptPassThrough(ISteamClientMap::GetISteamScreenshots),
    AdaptPassThrough(ISteamClientMap::GetISteamGameSearch),
    AdaptPassThrough(ISteamClientMap::RunFrame),
    AdaptPassThrough(ISteamClientMap::GetIPCCallCount),
    AdaptPassThrough(ISteamClientMap::SetWarningMessageHook),
    AdaptPassThrough(ISteamClientMap::BShutdownIfAllPipesClosed),
    AdaptPassThrough(ISteamClientMap::GetISteamHTTP),
    AdaptEmpty(ISteamClientMap::DEPRECATED_GetISteamUnifiedMessages),
    AdaptPassThrough(ISteamClientMap::GetISteamController),
    AdaptPassThrough(ISteamClientMap::GetISteamUGC),
    AdaptPassThrough(ISteamClientMap::GetISteamAppList),
    AdaptPassThrough(ISteamClientMap::GetISteamMusic),
    AdaptPassThrough(ISteamClientMap::GetISteamMusicRemote),
    AdaptPassThrough(ISteamClientMap::GetISteamHTMLSurface),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess),
    AdaptEmpty(ISteamClientMap::DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess),
    AdaptPassThrough(ISteamClientMap::Set_SteamAPI_CCheckCallbackRegisteredInProcess),
    AdaptPassThrough(ISteamClientMap::GetISteamInventory),
    AdaptPassThrough(ISteamClientMap::GetISteamVideo),
    AdaptPassThrough(ISteamClientMap::GetISteamParentalSettings),
    AdaptPassThrough(ISteamClientMap::GetISteamInput),
    AdaptPassThrough(ISteamClientMap::GetISteamParties),
};

AdaptExposeNoUser(ISteamClient019, ISteamClientMap, "SteamClient019");
