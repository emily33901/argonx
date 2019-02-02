#pragma once

namespace Steam {
enum class InterfaceTarget : u32 {
    user,
    appList,
    apps,
    client,
    engine,
    controller,
    friends,
    gameserver,
    remotestorage,
    ugc,
    userstats,
    utils,

    max
};

inline const char *InterfaceName(InterfaceTarget t) {
    const char *interfaceNames[] = {
        "SteamUser",
        "SteamAppList",
        "SteamApps",
        "SteamClient",
        "ClientEngine",
        "SteamController",
        "SteamFriends",
        "SteamGameServer",
        "SteamRemoteStorage",
        "SteamUGC",
        "SteamUserStats",
        "SteamUtils",
    };

    return interfaceNames[(u32)t];
}
} // namespace Steam