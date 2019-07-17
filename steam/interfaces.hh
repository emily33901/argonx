#pragma once

namespace Steam {
using UserHandle = u32;

constexpr UserHandle noUserHandle = ~0;

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

    argon,

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
        "Argon",
    };

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