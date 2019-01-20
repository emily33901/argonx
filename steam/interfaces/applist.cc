#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

// #include "Open Steamworks/AppListCommon.h"

namespace Reference {
#include "SteamStructs/IClientAppManager.h"
}

class IClientAppManager : public Reference::IClientAppManager {
public:
    // Inherited via IClientAppManager
    virtual unknown_ret InstallApp(unsigned int, int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret UninstallApp(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret LaunchApp(CGameID, unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ShutdownApp(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppInstallState(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppBuildID(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentAppSizeOnDisk(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetRequiredAppsSizeOnDisk(unsigned int const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppInstallDir(unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsAppDlcInstalled(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDlcDownloadProgress(unsigned int, unsigned int, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumInstalledApps() override {
        return unknown_ret();
    }
    virtual unknown_ret GetInstalledApps(unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppDependency(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDependentApps(unsigned int, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUpdateInfo(unsigned int, AppUpdateInfo_s *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppConfigValue(unsigned int, char const *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAppConfigValue(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsAppUpToDate(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAvailableLaunchOptions(unsigned int, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAvailableLanguages(unsigned int, bool, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsDlcEnabled(unsigned int, unsigned int, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDlcEnabled(unsigned int, unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret StartValidatingApp(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CancelValidation(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret MarkContentCorrupt(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetInstalledDepots(unsigned int, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFileDetails(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret VerifySignedFiles(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAvailableBetas(unsigned int, int *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret CheckBetaPassword(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret BHasCachedBetaPassword(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDownloadingEnabled(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsDownloadingEnabled() override {
        return unknown_ret();
    }
    virtual unknown_ret GetDownloadStats(DownloadStats_s *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDownloadingAppID() override {
        return unknown_ret();
    }
    virtual unknown_ret GetAutoUpdateTimeRestrictionEnabled() override {
        return unknown_ret();
    }
    virtual unknown_ret SetAutoUpdateTimeRestrictionEnabled(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAutoUpdateTimeRestrictionHours(int *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAutoUpdateTimeRestrictionStartHour(int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAutoUpdateTimeRestrictionEndHour(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppAutoUpdateBehavior(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAppAutoUpdateBehavior(unsigned int, EAppAutoUpdateBehavior) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAppAllowDownloadsWhileRunningBehavior(unsigned int, EAppAllowDownloadsWhileRunningBehavior) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppAllowDownloadsWhileRunningBehavior(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAllowDownloadsWhileAnyAppRunning(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret BAllowDownloadsWhileAnyAppRunning() override {
        return unknown_ret();
    }
    virtual unknown_ret ChangeAppDownloadQueuePlacement(unsigned int, EAppDownloadQueuePlacement) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppDownloadQueueIndex(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppAutoUpdateDelayedUntilTime(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumAppsInDownloadQueue() override {
        return unknown_ret();
    }
    virtual unknown_ret BHasLocalContentServer() override {
        return unknown_ret();
    }
    virtual unknown_ret BuildBackup(unsigned int, unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret BuildInstaller(char const *, char const *, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret CancelBackup() override {
        return unknown_ret();
    }
    virtual unknown_ret RestoreApp(unsigned int, int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret CanMoveApp(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret MoveApp(unsigned int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMoveAppProgress(unsigned int, unsigned long long *, unsigned long long *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret CancelMoveApp(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BNeedsFile(unsigned int, char const *, unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BAddFileOnDisk(unsigned int, char const *, unsigned long long, unsigned int, SHADigestWrapper_t) override {
        return unknown_ret();
    }
    virtual unknown_ret FinishAddingFiles(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppStateInfo(unsigned int, EAppReleaseState *, unsigned int *, unsigned int *, CSteamID *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsAvailableOnPlatform(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumInstallBaseFolders() override {
        return unknown_ret();
    }
    virtual unknown_ret GetInstallBaseFolder(int, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret AddInstallBaseFolder(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveInstallBaseFolder(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFreeDiskSpace(int) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetDiskSpaceStats(int, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppInstallBaseFolder(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ForceInstallDirOverride(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDownloadThrottleRateKbps(int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDownloadThrottleRateKbps(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SuspendDownloadThrottling(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetThrottleDownloadsWhileStreaming(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret BThrottleDownloadsWhileStreaming() override {
        return unknown_ret();
    }
    virtual unknown_ret GetLaunchQueryParam(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret BeginLaunchQueryParams(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLaunchQueryParam(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret CommitLaunchQueryParams(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLaunchCommandLine(unsigned int, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret AddContentLogLine(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSystemIconFile(unsigned int, char *, int) override {
        return unknown_ret();
    }
};

AdaptDeclare(ISteamAppList001);
AdaptDefine(ISteamAppList001, IClientAppManager, "STEAMAPPLIST_INTERFACE_VERSION001") = {
    AdaptPassThrough(IClientAppManager::GetNumInstalledApps),
    AdaptPassThrough(IClientAppManager::GetInstalledApps),
    AdaptEmpty(IClientAppManager::GetAppName),
    AdaptPassThrough(IClientAppManager::GetAppInstallDir),
    AdaptPassThrough(IClientAppManager::GetAppBuildID),
};
