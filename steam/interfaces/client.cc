#include <precompiled.hh>

#include <atomic>

#include <cpptoml/include/cpptoml.h>

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
static const char *InterfaceVersion(InterfaceTarget t, bool isServer) {
    auto base = InterfaceName(t);
    if (!isServer) {
        return base;
    }
    static char buf[256] = "";
    memset((void *)buf, 0, sizeof(buf));

    snprintf(buf, 255, "%sServer", base);

    return buf;
}

// Helper function to create a filled user interface storage
UserInterfaceStorage FillUserInterfaceStorage(UserHandle h, bool isServer) {
    auto storage = CreateUserInterfaceStorage();
    for (u32 i = 0; i < (u32)InterfaceTarget::max; i++) {
        int err    = 0;
        storage[i] = CreateInterfaceWithEither(InterfaceVersion((InterfaceTarget)i, isServer), h);

        AssertAlways(err == 0 && storage[i] != nullptr, "CreateInterface for target %s failed! (err = %d)", InterfaceVersion((InterfaceTarget)i, isServer), err);
    }

    return storage;
}

// The clients job (SteamClientMap / ClientEngineMap) is to deal with the ipc connection to the server
// by managing jobs and processing messages - reporting on dropped rpc connection, so on
// CMClients are only "created" when a user handle is created (you need 1 per user afterall).
// This behaviour is roughly on par with how steam deals with its cm connections - although it only has 1
// CMClient (afaik iirc).

// Keep track of how many pipes we have
static std::atomic_int pipeReferenceCount;

template <bool isServer>
class ClientEngineMap : Reference::IClientEngine {

    // This should not be called directly
    // Call CreateSteamPipe which will then call this!
    bool CreateClientPipe() {
        AssertClient();

        if (Steam::ClientPipe() == nullptr) {
            bool connected = false;

            const auto cfg       = cpptoml::parse_file("argonx_client.toml");
            const auto timeout   = cfg->get_qualified_as<int>("rpc.responseTimeout");
            const auto reconnect = cfg->get_qualified_as<int>("rpc.reconnectTime");

            Assert(timeout && reconnect, "Client config invalid!");

            Steam::JobManager::SetResponseTimeout(*timeout);
            Steam::SetClientPipe(new Pipe(false, Steam::rpcSocketAddress));
            Steam::ClientPipe()->processMessage = [&connected](Pipe::Target, u8 *data, u32 size) {
                LOG_SCOPE_F(INFO, "Client message");

                LOG_F(INFO, "size:%d", size);

                // Assume rpc job
                Buffer b;
                b.Write(std::make_pair(data, size));
                b.SetPos(0);

                auto jobId = b.Read<i64>();
                LOG_F(INFO, "jobId:%ld", jobId);

                if (jobId < 0) {
                    auto header = b.Read<Steam::RpcNonCallHeader>();

                    switch (header.t) {
                    case Steam::RpcType::connect: {
                        LOG_F(INFO, "Connected!");
                        connected = true;
                    } break;
                    case Steam::RpcType::heartbeat: {
                        LOG_F(INFO, "Recieved heartbeat response from server");
                    } break;
                    case Steam::RpcType::disconnect: {
                        // Server confirmed our disconnect
                        auto oldPipe = Steam::ClientPipe();
                        Steam::SetClientPipe(nullptr);
                        delete oldPipe;
                        LOG_F(WARNING, "Pipe destroyed successfully!");
                    } break;
                    }
                } else {
                    b.SetBaseAtCurPos();
                    Steam::JobManager::PostResult(jobId, b);
                }
            };

            Steam::ClientPipe()->SendMessage(0, Buffer{Steam::JobManager::GetNextNonCallJobId(), Steam::RpcType::connect});
            std::this_thread::sleep_for(std::chrono::seconds(*reconnect));
            Steam::ClientPipe()->ProcessMessages();

            if (!connected) {
                // Server isnt up
                // Cleanup and tell whoever called us it isnt
                delete Steam::ClientPipe();
                Steam::SetClientPipe(nullptr);

                return false;
            }

            std::thread pipeThread{[]() {
                loguru::set_thread_name("client");
                std::chrono::time_point<std::chrono::system_clock> lastHeartbeatSent;
                while (Steam::ClientPipe()) {
                    Steam::ClientPipe()->ProcessMessages();

                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1ms);

                    // TODO: heartbeats should really be part of the transport
                    // and not really our issue...
                    if ((std::chrono::system_clock::now() - lastHeartbeatSent) > 20s) {
                        auto b = Buffer{
                            Steam::JobManager::GetNextNonCallJobId(),
                            Steam::RpcNonCallHeader{Steam::RpcType::heartbeat},
                        };
                        Steam::ClientPipe()->SendMessage(0, b);

                        // Update the timepoints
                        lastHeartbeatSent = std::chrono::system_clock::now();
                    }
                }
            }};

            pipeThread.detach();
        }
        // Increment the reference count
        ++pipeReferenceCount;

        return true;
    }

public:
    // Inherited via IClientEngine
    virtual Steam::PipeHandle CreateSteamPipe() override {
        AssertClient();

        auto success = CreateClientPipe();

        if (success) {
            LOG_F(INFO, "Pipe created successfully!");
            return Steam::ClientPipe()->Id();
        }

        return 0;
    }
    virtual bool BReleaseSteamPipe(Steam::PipeHandle pipe) override {
        AssertClient();

        pipeReferenceCount--;

        if (pipeReferenceCount <= 0) {
            // Tell the server we are going bye bye
            auto b = Buffer{
                Steam::JobManager::GetNextNonCallJobId(),
                Steam::RpcNonCallHeader{Steam::RpcType::disconnect},
            };
            Steam::ClientPipe()->SendMessage(0, b);
        }

        if (pipeReferenceCount < 0) pipeReferenceCount = 0;

        return true;
    }
    virtual Steam::UserHandle CreateGlobalUser(Steam::PipeHandle *pipe) override {
        // TODO: This cannot be a no-op
        Assert(false, "CreateGlobalUser has not been implemented");
        return 1;
    }
    virtual Steam::UserHandle ConnectToGlobalUser(Steam::PipeHandle pipe) override {
        // TODO: This cannot be a no-op!
        Assert(false, "ConnectToGlobalUser has not been implemented");
        return 1;
    }
    virtual Steam::UserHandle CreateLocalUser(Steam::PipeHandle *pipe, EAccountType t) override {
        // TODO: this should probably hold onto the account type aswell...

        auto handle = [this, &pipe, &t]() {
            RpcMakeCallIfClientNoUser(CreateLocalUser, engine, pipe, t) {
                lastUserHandle += 1;

                userStorage.insert({lastUserHandle, FillUserInterfaceStorage(lastUserHandle, isServer)});

                return lastUserHandle;
            };
        }();

        RpcRunOnClient() {
            // Create the user storage and store it
            userStorage.insert({handle, FillUserInterfaceStorage(handle, isServer)});
        }

        return handle;
    }
    virtual void CreatePipeToLocalUser(Steam::UserHandle h, Steam::PipeHandle *pipe) override {
        // We need a valid steam pipe here in order to ask the server
        // whether this userhandle is valid!

        *pipe = CreateSteamPipe();

        if (*pipe == 0) {
            // We cant even connect to the server
            // which means this cant happen right now
            return;
        }

        auto serverResult = [this, &pipe, &h]() {
            // No code inside here as we call IsValidHSteamUserPipe to check if this use handle is correct
            // not our own function.
            RpcMakeCallIfClientNoUser(IsValidHSteamUserPipe, engine, *pipe, h) {
                return false;
            }
        }();

        RpcRunOnClient() {
            if (serverResult) {
                // Create a local user storage if it does not already exist
                if (userStorage.find(h) == userStorage.end())
                    userStorage.insert({h, FillUserInterfaceStorage(h, isServer)});
            } else {
                // Not valid so get rid of the pipe now
                BReleaseSteamPipe(*pipe);
            }
        }
    }
    virtual void ReleaseUser(Steam::PipeHandle pipe, Steam::UserHandle h) override {
        RpcRunOnBothNoUser(ReleaseUser, engine, pipe, h) {
            if (userStorage.find(h) != userStorage.end()) {
                Defer(userStorage.erase(h));

                auto s = userStorage[h];

                for (auto i = 0; i < (u32)InterfaceTarget::max; i++) {
                    // Call the interfaces destructor
                    DestroyInterface(InterfaceVersion((InterfaceTarget)i, isServer), s[i]);

                    // Make it obvious if there is a use after free
                    // This will also trigger the assert in the server rpc handler
                    s[i] = nullptr;
                }

                delete[] s;
            }
        }
    }
    virtual bool IsValidHSteamUserPipe(Steam::PipeHandle pipe, Steam::UserHandle h) override {
        RpcRunOnClient() {
            // If this pipe is invalid then how can we check if the user is valid?
            if (pipe == 0 || Steam::ClientPipe() == nullptr) return false;
        }

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
    virtual unknown_ret SetLocalIPBinding(SteamIPAddress_t const &, unsigned short) override {
        return unknown_ret();
    }
    virtual const char *GetUniverseName(EUniverse e) override {
        switch (e) {
        case Steam::k_EUniverseInvalid:
            return "Invalid";
        case Steam::k_EUniversePublic:
            return "Public";
        case Steam::k_EUniverseBeta:
            return "Beta";
        case Steam::k_EUniverseInternal:
            return "Internal";
        case Steam::k_EUniverseDev:
            return "Dev";
        default:
            return "Invalid";
        }
    }
    virtual void *GetIClientFriends(Steam::UserHandle h, Steam::PipeHandle p) override {
        if (IsValidHSteamUserPipe(p, h)) {
            return Steam::GetUserInterface(h, InterfaceTarget::friends);
        }
        return nullptr;
    }
    virtual void *GetIClientUtils(Steam::PipeHandle p) override {
        // TODO: name a constant for bad pipe!
        if (p == 0) return nullptr;

        return Steam::GetUserInterface(noUserHandle, InterfaceTarget::utils);
    }
    virtual void *GetIClientBilling(Steam::UserHandle h, Steam::PipeHandle p) override {
        if (p == 0) return nullptr;

        return Steam::GetUserInterface(h, InterfaceTarget::billing);
    }
    virtual void *GetIClientMatchmaking(Steam::UserHandle h, Steam::PipeHandle p) override {
        if (p == 0) return nullptr;

        return Steam::GetUserInterface(h, InterfaceTarget::matchmaking);
    }
    virtual void *GetIClientApps(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientMatchmakingServers(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientGameSearch(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret RunFrame() override {
        return unknown_ret();
    }
    virtual unknown_ret GetIPCCallCount() override {
        return unknown_ret();
    }
    virtual void *GetIClientUserStats(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientGameServerStats(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientNetworking(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientRemoteStorage(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientScreenshots(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret SetWarningMessageHook(void (*)(int, char const *)) override {
        return unknown_ret();
    }
    virtual void *GetIClientGameCoordinator(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret SetOverlayNotificationPosition(ENotificationPosition) override {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayNotificationInset(Steam::UserHandle h, Steam::PipeHandle p) override {
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
    virtual void *GetIClientProductBuilder(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientDepotBuilder(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientNetworkDeviceManager(int) override {
        return nullptr;
    }
    virtual unknown_ret ConCommandInit(IConCommandBaseAccessor *) override {
        return unknown_ret();
    }
    virtual void *GetIClientAppManager(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientConfigStore(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret BOverlayNeedsPresent() override {
        return unknown_ret();
    }
    virtual void *GetIClientGameStats(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientHTTP(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret FlushBeforeValidate() override {
        return unknown_ret();
    }
    virtual unknown_ret BShutdownIfAllPipesClosed() override {
        return unknown_ret();
    }
    virtual void *GetIClientAudio(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientMusic(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientUnifiedMessages(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientController(Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientParentalSettings(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientStreamLauncher(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientDeviceAuth(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientRemoteClientManager(int) override {
        return nullptr;
    }
    virtual void *GetIClientStreamClient(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientShortcuts(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientUGC(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientInventory(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientVR(int) override {
        return nullptr;
    }
    virtual void *GetIClientGameNotifications(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientHTMLSurface(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientVideo(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientControllerSerialized(int) override {
        return nullptr;
    }
    virtual void *GetIClientAppDisableUpdate(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret Set_Client_API_CCheckCallbackRegisteredInProcess(unsigned int (*)(int)) override {
        return unknown_ret();
    }
    virtual void *GetIClientBluetoothManager(int) override {
        return nullptr;
    }
    virtual void *GetIClientSharedConnection(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientShader(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientNetworkingSocketsSerialized(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual void *GetIClientCompat(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }
    virtual unknown_ret SetClientCommandLine(int, char **) override {
        return unknown_ret();
    }
    virtual void *GetIClientParties(Steam::UserHandle h, Steam::PipeHandle p) override {
        return nullptr;
    }

    void *GetIClientNetworkingMessages(int, int) override {
        return nullptr;
    }
    void *GetIClientNetworkingSockets(int, int) override {
        return nullptr;
    }
    void *GetIClientNetworkingUtils(int) override {
        return nullptr;
    }
    void *GetIClientNetworkingUtilsSerialized(int) override {
        return nullptr;
    }
    void *GetIClientSTARInternal(int, int) override {
        return nullptr;
    }
    void *GetIClientRemotePlay(int, int) override {
        return nullptr;
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
