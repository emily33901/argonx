#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

#include "Open Steamworks/AppsCommon.h"

namespace Reference {
#include "SteamStructs/IClientApps.h"
}

#include "argonx/cmclient/steamhandlers.hh"
#include "language_internal.hh"
#include "steammessages_base.pb.h"
#include "steammessages_clientserver.pb.h"

struct License {
    u32                       packageId;
    u32                       timeCreated;
    u32                       timeNextProcess;
    i32                       minuteLimit;
    i32                       minutesUsed;
    u32                       paymentMethod;
    Steam::EAppOwnershipFlags flags;
    std::string               purchaseCountryCode;
    i32                       territoryCode;
    i32                       changeNumber;
    u32                       ownerId;
    u32                       initialPeriod;
    u32                       initialTimeUnit;
    u32                       renewalPeriod;
    u32                       renewalTimeUnit;
};

template <bool isServer>
class ClientAppsMap : public Reference::IClientApps {

    std::vector<License> licenses;

public:
    static void OnClientLicenseList(Argonx::CMClient *c, u32 msgSize, Buffer &b, u64 jobId) {
        auto msg = b.ReadAsProto<CMsgClientLicenseList>(msgSize);

        auto apps = LookupInterface<ClientAppsMap<true>>(c, Steam::InterfaceTarget::apps);

        for (auto &license : msg.licenses()) {
            LOG_F(INFO, "Got license for package %d", license.package_id());

            apps->licenses.push_back({
                license.package_id(),
                license.time_created(),
                license.time_next_process(),
                license.minute_limit(),
                license.minutes_used(),
                license.payment_method(),
                (Steam::EAppOwnershipFlags)license.flags(),
                license.purchase_country_code(),
                license.territory_code(),
                license.change_number(),
                license.owner_id(),
                license.initial_period(),
                license.initial_time_unit(),
                license.renewal_period(),
                license.renewal_time_unit(),
            });
        }
    }

public:
    ClientAppsMap(UserHandle h) {}

    // Inherited via IClientApps
    unknown_ret GetAppData(unsigned int, char const *, char *, int) override {
        return unknown_ret();
    }
    unknown_ret SetLocalAppConfig(unsigned int, unsigned char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetInternalAppIDFromGameID(CGameID) override {
        return unknown_ret();
    }
    unknown_ret GetAllOwnedMultiplayerApps(unsigned int *, int) override {
        return unknown_ret();
    }
    unknown_ret GetAvailableLaunchOptions(unsigned int, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppDataSection(unsigned int, int, unsigned char *, int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetMultipleAppDataSections(unsigned int, int const *, int, unsigned char *, int, bool, int *) override {
        return unknown_ret();
    }
    unknown_ret RequestAppInfoUpdate(unsigned int const *, int) override {
        return unknown_ret();
    }
    unknown_ret GetDLCCount(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BGetDLCDataByIndex(unsigned int, int, unsigned int *, bool *, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetAppType(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetStoreTagLocalization(ELanguage, unsigned int *, int, unsigned char *, int) override {
        return unknown_ret();
    }
};

RegisterHelperUnique(Argonx::EMsg::ClientLicenseList, ClientAppsMap<true>::OnClientLicenseList);

AdaptExposeClientServer(ClientAppsMap, "SteamApps");

using IClientAppsMap = ClientAppsMap<false>;

AdaptDeclare(ISteamApps001);
AdaptDefine(ISteamApps001, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION001") = {
    AdaptPassThrough(IClientAppsMap::GetAppData),
};
AdaptDeclare(ISteamApps003);
AdaptDefine(ISteamApps003, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION003") = {
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
AdaptDefine(ISteamApps004, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION004") = {
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
AdaptDefine(ISteamApps005, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION005") = {
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
AdaptDefine(ISteamApps006, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION006") = {
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
AdaptDefine(ISteamApps007, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION007") = {
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
AdaptDefine(ISteamApps008, IClientAppsMap, "STEAMAPPS_INTERFACE_VERSION008") = {
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
