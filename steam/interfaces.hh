#pragma once

namespace Steam {
enum class InterfaceTarget : u32 {
    user,
    appList,
    apps,
    client,
    controller,
    friends,
    gameserver,
    remotestorage,
    ugc,
    userstats,
    utils,

    max
};

inline const char *interfaceNames[] = {
    "SteamUser",
    "SteamAppList",
    "SteamApps",
    "SteamClient",
    "SteamController",
    "SteamFriends",
    "SteamGameServer",
    "SteamRemoteStorage",
    "SteamUGC",
    "SteamUserStats",
    "SteamUtils",
};
} // namespace Steam