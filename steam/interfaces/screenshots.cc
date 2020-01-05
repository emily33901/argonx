#include <precompiled.hh>

#include "helpers.hh"

#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientScreenshots.h"
}

template <bool isServer>
class ClientScreenshots : public Reference::IClientScreenshots {
public:
    UserHandle userHandle;
    ClientScreenshots(UserHandle h) : userHandle(h) {}

    unknown_ret GetShortcutDisplayName(CGameID) override {
      return unknown_ret();
    }
    unknown_ret SetShortcutDisplayName(CGameID, char const *) override {
        return unknown_ret();
    }
    unknown_ret WriteScreenshot(CGameID, void *, unsigned int, int, int) override {
        return unknown_ret();
    }
    unknown_ret AddScreenshotToLibrary(CGameID, EVRScreenshotType, char const *, char const *, char const *, int, int) override {
        return unknown_ret();
    }
    unknown_ret TriggerScreenshot(CGameID) override {
        return unknown_ret();
    }
    unknown_ret RequestScreenshotFromGame(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetLocation(CGameID, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret TagUser(CGameID, unsigned int, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret TagPublishedFile(CGameID, unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret ResolvePath(CGameID, unsigned int, EScreenshotFile, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetSizeOnDisk(CGameID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetSizeInCloud(CGameID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsPersisted(CGameID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetNumGamesWithLocalScreenshots() override {
        return unknown_ret();
    }
    unknown_ret GetGameWithLocalScreenshots(int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalScreenshotCount(CGameID) override {
        return unknown_ret();
    }
    unknown_ret GetLocalScreenshot(CGameID, int, unsigned int *, int *, int *, unsigned int *, EUCMFilePrivacyState *, unsigned long long *, char *, unsigned int, bool *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalScreenshotByHandle(CGameID, unsigned int, int *, int *, unsigned int *, EUCMFilePrivacyState *, unsigned long long *, char *, unsigned int, bool *) override {
        return unknown_ret();
    }
    unknown_ret SetLocalScreenshotCaption(CGameID, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetLocalScreenshotPrivacy(CGameID, unsigned int, EUCMFilePrivacyState) override {
        return unknown_ret();
    }
    unknown_ret SetLocalScreenshotSpoiler(CGameID, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret StartBatch(CGameID) override {
        return unknown_ret();
    }
    unknown_ret AddToBatch(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret UploadBatch(EUCMFilePrivacyState) override {
        return unknown_ret();
    }
    unknown_ret DeleteBatch(bool) override {
        return unknown_ret();
    }
    unknown_ret CancelBatch() override {
        return unknown_ret();
    }
    unknown_ret RecoverOldScreenshots() override {
        return unknown_ret();
    }
    unknown_ret GetTaggedUserCount(CGameID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetTaggedUser(CGameID, unsigned int, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocation(CGameID, unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetTaggedPublishedFileCount(CGameID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetTaggedPublishedFile(CGameID, unsigned int, int) override {
        return unknown_ret();
    }
    unknown_ret GetScreenshotVRType(CGameID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BGetUserScreenshotDirectory(char *, unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientScreenshots, "SteamScreenshots");

using IClientScreenshots = ClientScreenshots<false>;

AdaptDeclare(ISteamScreenshots003);
AdaptDefine(ISteamScreenshots003, IClientScreenshots, "SteamScreenshots003") = {
    AdaptPassThrough(IClientScreenshots::WriteScreenshot),
    AdaptPassThrough(IClientScreenshots::AddScreenshotToLibrary),
    AdaptPassThrough(IClientScreenshots::TriggerScreenshot),
    AdaptEmpty(IClientScreenshots::HookScreenshots),
    AdaptPassThrough(IClientScreenshots::SetLocation),
    AdaptPassThrough(IClientScreenshots::TagUser),
    AdaptPassThrough(IClientScreenshots::TagPublishedFile),
    AdaptEmpty(IClientScreenshots::IsScreenshotsHooked),
    AdaptEmpty(IClientScreenshots::AddVRScreenshotToLibrary),
};
AdaptDeclare(ISteamScreenshots002);
AdaptDefine(ISteamScreenshots002, IClientScreenshots, "SteamScreenshots002") = {
    AdaptPassThrough(IClientScreenshots::WriteScreenshot),
    AdaptPassThrough(IClientScreenshots::AddScreenshotToLibrary),
    AdaptPassThrough(IClientScreenshots::TriggerScreenshot),
    AdaptEmpty(IClientScreenshots::HookScreenshots),
    AdaptPassThrough(IClientScreenshots::SetLocation),
    AdaptPassThrough(IClientScreenshots::TagUser),
    AdaptPassThrough(IClientScreenshots::TagPublishedFile),
};
AdaptDeclare(ISteamScreenshots001);
AdaptDefine(ISteamScreenshots001, IClientScreenshots, "SteamScreenshots001") = {
    AdaptPassThrough(IClientScreenshots::WriteScreenshot),
    AdaptPassThrough(IClientScreenshots::AddScreenshotToLibrary),
    AdaptPassThrough(IClientScreenshots::TriggerScreenshot),
    AdaptEmpty(IClientScreenshots::HookScreenshots),
    AdaptPassThrough(IClientScreenshots::SetLocation),
    AdaptPassThrough(IClientScreenshots::TagUser),
};
