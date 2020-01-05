
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientShortcuts.h"
}

template <bool isServer>
class ClientShortcuts : public Reference::IClientShortcuts {
public:
    UserHandle userHandle;
    ClientShortcuts(UserHandle h) : userHandle(h) {}

    unknown_ret GetUniqueLocalAppId() override {
        return unknown_ret();
    }
    unknown_ret GetGameIDForAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppIDForGameID(CGameID) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutCount() override {
        return unknown_ret();
    }
    unknown_ret GetShortcutAppIDByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutAppNameByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutExeByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutUserTagCountByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutUserTagByIndex(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsShortcutRemoteByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsTemporaryShortcutByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsOpenVRShortcutByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsDevkitShortcutByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDevkitGameIDByIndex(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetDevkitAppIDByDevkitGameID(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutAppNameByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutExeByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutStartDirByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutIconByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutPathByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutCommandLine(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutUserTagCountByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutUserTagByAppID(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsShortcutRemoteByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsShortcutHiddenByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsTemporaryShortcutByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsOpenVRShortcutByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BAllowDesktopConfigByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BAllowOverlayByAppID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetShortcutLastPlayedTime(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AddShortcut(char const *, char const *, char const *, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddTemporaryShortcut(char const *, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddOpenVRShortcut(char const *, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutFromFullpath(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutAppName(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutExe(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutStartDir(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutIcon(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutCommandLine(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret ClearShortcutUserTags(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AddShortcutUserTag(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret RemoveShortcutUserTag(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret ClearAndSetShortcutUserTags(unsigned int, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    unknown_ret SetShortcutHidden(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetAllowDesktopConfig(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetAllowOverlay(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetOpenVRShortcut(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetDevkitShortcut(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret RemoveShortcut(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RemoveAllTemporaryShortcuts() override {
        return unknown_ret();
    }
    unknown_ret LaunchShortcut(unsigned int, unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientShortcuts, "SteamShortcuts");

using IClientShortcuts = ClientShortcuts<false>;
