#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

#include "Open Steamworks/AppsCommon.h"

namespace Reference {
#include "SteamStructs/IClientApps.h"
}

class IClientAppsMap : public Reference::IClientApps {
public:
    // Inherited via IClientApps
    virtual unknown_ret GetAppData(unsigned int, char const *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLocalAppConfig(unsigned int, unsigned char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetInternalAppIDFromGameID(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAllOwnedMultiplayerApps(unsigned int *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppDataSection(unsigned int, int, unsigned char *, int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestAppInfoUpdate(unsigned int const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDLCCount(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetDLCDataByIndex(unsigned int, int, unsigned int *, bool *, char *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppType(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStoreTagLocalization(ELanguage, unsigned int *, int, unsigned char *, int) override {
        return unknown_ret();
    }
};

AdaptDeclare(ISteamApps001);
AdaptDefine(ISteamApps001) = {
    AdaptPassThrough(IClientAppsMap::GetAppData),
};
AdaptDeclare(ISteamApps003);
AdaptDefine(ISteamApps003) = {
    AdaptEmpty(IClientAppsMap::BIsSubscribed),
    AdaptEmpty(IClientAppsMap::BIsLowViolence),
    AdaptEmpty(IClientAppsMap::BIsCybercafe),
    AdaptEmpty(IClientAppsMap::BIsVACBanned),
    AdaptEmpty(IClientAppsMap::GetCurrentGameLanguage),
    AdaptEmpty(IClientAppsMap::GetAvailableGameLanguages),
    AdaptEmpty(IClientAppsMap::BIsSubscribedApp),
    AdaptEmpty(IClientAppsMap::BIsDlcInstalled),
};
AdaptDeclare(ISteamApps004);
AdaptDefine(ISteamApps004) = {
    AdaptEmpty(IClientAppsMap::BIsSubscribed),
    AdaptEmpty(IClientAppsMap::BIsLowViolence),
    AdaptEmpty(IClientAppsMap::BIsCybercafe),
    AdaptEmpty(IClientAppsMap::BIsVACBanned),
    AdaptEmpty(IClientAppsMap::GetCurrentGameLanguage),
    AdaptEmpty(IClientAppsMap::GetAvailableGameLanguages),
    AdaptEmpty(IClientAppsMap::BIsSubscribedApp),
    AdaptEmpty(IClientAppsMap::BIsDlcInstalled),
    AdaptEmpty(IClientAppsMap::GetEarliestPurchaseUnixTime),
    AdaptEmpty(IClientAppsMap::BIsSubscribedFromFreeWeekend),
    AdaptPassThrough(IClientAppsMap::GetDLCCount),
    AdaptPassThrough(IClientAppsMap::BGetDLCDataByIndex),
    AdaptEmpty(IClientAppsMap::InstallDLC),
    AdaptEmpty(IClientAppsMap::UninstallDLC),
};
AdaptDeclare(ISteamApps005);
AdaptDefine(ISteamApps005) = {
    AdaptEmpty(IClientAppsMap::BIsSubscribed),
    AdaptEmpty(IClientAppsMap::BIsLowViolence),
    AdaptEmpty(IClientAppsMap::BIsCybercafe),
    AdaptEmpty(IClientAppsMap::BIsVACBanned),
    AdaptEmpty(IClientAppsMap::GetCurrentGameLanguage),
    AdaptEmpty(IClientAppsMap::GetAvailableGameLanguages),
    AdaptEmpty(IClientAppsMap::BIsSubscribedApp),
    AdaptEmpty(IClientAppsMap::BIsDlcInstalled),
    AdaptEmpty(IClientAppsMap::GetEarliestPurchaseUnixTime),
    AdaptEmpty(IClientAppsMap::BIsSubscribedFromFreeWeekend),
    AdaptPassThrough(IClientAppsMap::GetDLCCount),
    AdaptPassThrough(IClientAppsMap::BGetDLCDataByIndex),
    AdaptEmpty(IClientAppsMap::InstallDLC),
    AdaptEmpty(IClientAppsMap::UninstallDLC),
    AdaptEmpty(IClientAppsMap::RequestAppProofOfPurchaseKey),
    AdaptEmpty(IClientAppsMap::GetCurrentBetaName),
    AdaptEmpty(IClientAppsMap::MarkContentCorrupt),
    AdaptEmpty(IClientAppsMap::GetInstalledDepots),
    AdaptEmpty(IClientAppsMap::GetAppInstallDir),
    AdaptEmpty(IClientAppsMap::BIsAppInstalled),
};
AdaptDeclare(ISteamApps006);
AdaptDefine(ISteamApps006) = {
    AdaptEmpty(IClientAppsMap::BIsSubscribed),
    AdaptEmpty(IClientAppsMap::BIsLowViolence),
    AdaptEmpty(IClientAppsMap::BIsCybercafe),
    AdaptEmpty(IClientAppsMap::BIsVACBanned),
    AdaptEmpty(IClientAppsMap::GetCurrentGameLanguage),
    AdaptEmpty(IClientAppsMap::GetAvailableGameLanguages),
    AdaptEmpty(IClientAppsMap::BIsSubscribedApp),
    AdaptEmpty(IClientAppsMap::BIsDlcInstalled),
    AdaptEmpty(IClientAppsMap::GetEarliestPurchaseUnixTime),
    AdaptEmpty(IClientAppsMap::BIsSubscribedFromFreeWeekend),
    AdaptPassThrough(IClientAppsMap::GetDLCCount),
    AdaptPassThrough(IClientAppsMap::BGetDLCDataByIndex),
    AdaptEmpty(IClientAppsMap::InstallDLC),
    AdaptEmpty(IClientAppsMap::UninstallDLC),
    AdaptEmpty(IClientAppsMap::RequestAppProofOfPurchaseKey),
    AdaptEmpty(IClientAppsMap::GetCurrentBetaName),
    AdaptEmpty(IClientAppsMap::MarkContentCorrupt),
    AdaptEmpty(IClientAppsMap::GetInstalledDepots),
    AdaptEmpty(IClientAppsMap::GetAppInstallDir),
    AdaptEmpty(IClientAppsMap::BIsAppInstalled),
    AdaptEmpty(IClientAppsMap::GetAppOwner),
    AdaptEmpty(IClientAppsMap::GetLaunchQueryParam),
    AdaptEmpty(IClientAppsMap::GetDlcDownloadProgress),
};
AdaptDeclare(ISteamApps007);
AdaptDefine(ISteamApps007) = {
    AdaptEmpty(IClientAppsMap::BIsSubscribed),
    AdaptEmpty(IClientAppsMap::BIsLowViolence),
    AdaptEmpty(IClientAppsMap::BIsCybercafe),
    AdaptEmpty(IClientAppsMap::BIsVACBanned),
    AdaptEmpty(IClientAppsMap::GetCurrentGameLanguage),
    AdaptEmpty(IClientAppsMap::GetAvailableGameLanguages),
    AdaptEmpty(IClientAppsMap::BIsSubscribedApp),
    AdaptEmpty(IClientAppsMap::BIsDlcInstalled),
    AdaptEmpty(IClientAppsMap::GetEarliestPurchaseUnixTime),
    AdaptEmpty(IClientAppsMap::BIsSubscribedFromFreeWeekend),
    AdaptPassThrough(IClientAppsMap::GetDLCCount),
    AdaptPassThrough(IClientAppsMap::BGetDLCDataByIndex),
    AdaptEmpty(IClientAppsMap::InstallDLC),
    AdaptEmpty(IClientAppsMap::UninstallDLC),
    AdaptEmpty(IClientAppsMap::RequestAppProofOfPurchaseKey),
    AdaptEmpty(IClientAppsMap::GetCurrentBetaName),
    AdaptEmpty(IClientAppsMap::MarkContentCorrupt),
    AdaptEmpty(IClientAppsMap::GetInstalledDepots),
    AdaptEmpty(IClientAppsMap::GetAppInstallDir),
    AdaptEmpty(IClientAppsMap::BIsAppInstalled),
    AdaptEmpty(IClientAppsMap::GetAppOwner),
    AdaptEmpty(IClientAppsMap::GetLaunchQueryParam),
    AdaptEmpty(IClientAppsMap::GetDlcDownloadProgress),
    AdaptEmpty(IClientAppsMap::GetAppBuildId),
    AdaptEmpty(IClientAppsMap::RequestAllProofOfPurchaseKeys),
};
AdaptDeclare(ISteamApps008);
AdaptDefine(ISteamApps008) = {
    AdaptEmpty(IClientAppsMap::BIsSubscribed),
    AdaptEmpty(IClientAppsMap::BIsLowViolence),
    AdaptEmpty(IClientAppsMap::BIsCybercafe),
    AdaptEmpty(IClientAppsMap::BIsVACBanned),
    AdaptEmpty(IClientAppsMap::GetCurrentGameLanguage),
    AdaptEmpty(IClientAppsMap::GetAvailableGameLanguages),
    AdaptEmpty(IClientAppsMap::BIsSubscribedApp),
    AdaptEmpty(IClientAppsMap::BIsDlcInstalled),
    AdaptEmpty(IClientAppsMap::GetEarliestPurchaseUnixTime),
    AdaptEmpty(IClientAppsMap::BIsSubscribedFromFreeWeekend),
    AdaptPassThrough(IClientAppsMap::GetDLCCount),
    AdaptPassThrough(IClientAppsMap::BGetDLCDataByIndex),
    AdaptEmpty(IClientAppsMap::InstallDLC),
    AdaptEmpty(IClientAppsMap::UninstallDLC),
    AdaptEmpty(IClientAppsMap::RequestAppProofOfPurchaseKey),
    AdaptEmpty(IClientAppsMap::GetCurrentBetaName),
    AdaptEmpty(IClientAppsMap::MarkContentCorrupt),
    AdaptEmpty(IClientAppsMap::GetInstalledDepots),
    AdaptEmpty(IClientAppsMap::GetAppInstallDir),
    AdaptEmpty(IClientAppsMap::BIsAppInstalled),
    AdaptEmpty(IClientAppsMap::GetAppOwner),
    AdaptEmpty(IClientAppsMap::GetLaunchQueryParam),
    AdaptEmpty(IClientAppsMap::GetDlcDownloadProgress),
    AdaptEmpty(IClientAppsMap::GetAppBuildId),
    AdaptEmpty(IClientAppsMap::RequestAllProofOfPurchaseKeys),
    AdaptEmpty(IClientAppsMap::GetFileDetails),
    AdaptEmpty(IClientAppsMap::GetLaunchCommandLine),
};