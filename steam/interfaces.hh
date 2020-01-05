#pragma once

#include "platform.hh"

namespace Steam {
using UserHandle = u32;

constexpr UserHandle noUserHandle = ~0;

// TODO: clean up these names / orders
enum class InterfaceTarget : u32 {
    user,
    appList,
    apps,
    billing,
    client,
    controller,
    engine,
    friends,
    gameserver,
    gameSearch,
    networking,

    matchmaking,
    matchmakingServers,
    remotestorage,
    ugc,
    userstats,
    utils,

    screenshots,
    productBuilder,
    depotBuilder,
    networkDeviceManager,
    appManager,
    configStore,
    gameStats,
    http,
    audio,
    music,
    unifiedMessages,
    parentalSettings,
    streamLauncher,
    shortcuts,
    inventory,
    vr,
    gameNotifications,
    htmlSurface,
    video,
    controllerSerialized,
    appDisableUpdate,
    bluetoothManager,
    sharedConnection,
    shader,
    networkingSocketsSerialized, // Not implemented
    compat,
    parties,

    argon,

    max
};

inline constexpr const char *InterfaceName(InterfaceTarget t) {
    const char *interfaceNames[] = {
        "SteamUser",
        "SteamAppList",
        "SteamApps",
        "SteamBilling",
        "SteamClient",
        "SteamController",
        "ClientEngine",
        "SteamFriends",
        "SteamGameServer",
        "SteamGameSearch",
        "SteamNetworking",
        "SteamMatchmaking",
        "SteamMatchmakingServers",
        "SteamRemoteStorage",
        "SteamUGC",
        "SteamUserStats",
        "SteamUtils",

        "SteamScreenshots",
        "SteamProductBuilder",
        "SteamDepotBuilder",
        "SteamNetworkDeviceManager",
        "SteamAppManager",
        "SteamConfigStore",
        "SteamGameStats",
        "SteamHTTP",
        "SteamAudio",
        "SteamMusic",
        "SteamUnifiedMessages",
        "SteamParentalSettings",
        "SteamStreamLauncher",
        "SteamShortcuts",
        "SteamInventory",
        "SteamVR",
        "SteamGameNotifications",
        "SteamHTMLSurface",
        "SteamVideo",
        "SteamControllerSerialized",
        "SteamAppDisableUpdate",
        "SteamBluetoothManager",
        "SteamSharedConnection",
        "SteamShader",
        "SteamNetworkingSocketsSerialized",
        "SteamCompat",
        "SteamParties",

        "Argon",
    };

    static_assert(Platform::ArrayLength(interfaceNames) == (u32)InterfaceTarget::max,
                  "Interface targets and strings do not match!");

    return interfaceNames[(u32)t];
}

// TODO: We should probably use a more robust type here.
using UserInterfaceStorage = void **;

UserInterfaceStorage CreateUserInterfaceStorage();
void *               GetUserInterface(Steam::UserHandle h, InterfaceTarget t);

void *CreateInterfaceWithUser(const char *name, Steam::UserHandle h);
void *CreateInterfaceWithEither(const char *name, Steam::UserHandle h);
void *CreateInterface(const char *name, int *err);
void  DestroyInterface(const char *name, void *v);
} // namespace Steam
