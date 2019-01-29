#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientUGC.h"
}

template<bool isServer>
class ClientUGCMap : public Reference::IClientUGC {
public:
    // Inherited via IClientUGC
    virtual unknown_ret CreateQueryUserUGCRequest(unsigned int, EUserUGCList, EUGCMatchingUGCType, EUserUGCListSortOrder, unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateQueryAllUGCRequest(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateQueryAllUGCRequest(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateQueryUGCDetailsRequest(unsigned long long *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SendQueryUGCRequest(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCResult(unsigned long long, unsigned int, SteamUGCDetails_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCPreviewURL(unsigned long long, unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCImageURL(unsigned long long, unsigned int, char *, unsigned int, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCMetadata(unsigned long long, unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCChildren(unsigned long long, unsigned int, unsigned long long *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCStatistic(unsigned long long, unsigned int, EItemStatistic, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCNumAdditionalPreviews(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCAdditionalPreview(unsigned long long, unsigned int, unsigned int, char *, unsigned int, char *, unsigned int, EItemPreviewType *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCNumKeyValueTags(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCKeyValueTag(unsigned long long, unsigned int, unsigned int, char *, unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQueryUGCIsDepotBuild(unsigned long long, unsigned int, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret ReleaseQueryUGCRequest(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret AddRequiredTag(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret AddExcludedTag(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnOnlyIDs(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnKeyValueTags(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnLongDescription(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnMetadata(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnChildren(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnAdditionalPreviews(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnTotalOnly(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetReturnPlaytimeStats(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLanguage(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAllowCachedResponse(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetCloudFileNameFilter(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetMatchAnyTag(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSearchText(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetRankedByTrendDays(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret AddRequiredKeyValueTag(unsigned long long, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestUGCDetails(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateItem(unsigned int, EWorkshopFileType) override {
        return unknown_ret();
    }
    virtual unknown_ret StartItemUpdate(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemTitle(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemDescription(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemUpdateLanguage(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemMetadata(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemVisibility(unsigned long long, ERemoteStoragePublishedFileVisibility) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemTags(unsigned long long, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemContent(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetItemPreview(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAllowLegacyUpload(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveItemKeyValueTags(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret AddItemKeyValueTag(unsigned long long, char const *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret AddItemPreviewFile(unsigned long long, char const *, EItemPreviewType) override {
        return unknown_ret();
    }
    virtual unknown_ret AddItemPreviewVideo(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdateItemPreviewFile(unsigned long long, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdateItemPreviewVideo(unsigned long long, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveItemPreview(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SubmitItemUpdate(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetItemUpdateProgress(unsigned long long, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetUserItemVote(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserItemVote(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret AddItemToFavorites(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveItemFromFavorites(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret SubscribeItem(unsigned int, unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret UnsubscribeItem(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumSubscribedItems(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSubscribedItems(unsigned int, unsigned long long *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetItemState(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetItemInstallInfo(unsigned int, unsigned long long, unsigned long long *, char *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetItemDownloadInfo(unsigned int, unsigned long long, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret DownloadItem(unsigned int, unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppItemsStatus(unsigned int, bool *, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret BInitWorkshopForGameServer(unsigned int, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SuspendDownloads(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAllItemsSizeOnDisk(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret StartPlaytimeTracking(unsigned int, unsigned long long *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret StopPlaytimeTracking(unsigned int, unsigned long long *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret StopPlaytimeTrackingForAllItems(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret AddDependency(unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveDependency(unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret AddAppDependency(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveAppDependency(unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppDependencies(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret DeleteItem(unsigned long long) override {
        return unknown_ret();
    }
};

using IClientUGCMap = ClientUGCMap<false>;


AdaptDeclare(ISteamUGC001);
AdaptDefine(ISteamUGC001, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION001") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
};
AdaptDeclare(ISteamUGC002);
AdaptDefine(ISteamUGC002, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION002") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptEmpty(IClientUGCMap::GetItemUpdateInfo),
};
AdaptDeclare(ISteamUGC003);
AdaptDefine(ISteamUGC003, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION003") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptEmpty(IClientUGCMap::GetItemUpdateInfo),
};
AdaptDeclare(ISteamUGC004);
AdaptDefine(ISteamUGC004, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION004") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
};
AdaptDeclare(ISteamUGC005);
AdaptDefine(ISteamUGC005, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION005") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
};
AdaptDeclare(ISteamUGC006);
AdaptDefine(ISteamUGC006, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION006") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
};
AdaptDeclare(ISteamUGC007);
AdaptDefine(ISteamUGC007, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION007") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumKeyValueTags),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCKeyValueTag),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnKeyValueTags),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::AddRequiredKeyValueTag),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::RemoveItemKeyValueTags),
    AdaptPassThrough(IClientUGCMap::AddItemKeyValueTag),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
    AdaptPassThrough(IClientUGCMap::BInitWorkshopForGameServer),
    AdaptPassThrough(IClientUGCMap::SuspendDownloads),
};
AdaptDeclare(ISteamUGC008);
AdaptDefine(ISteamUGC008, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION008") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumKeyValueTags),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCKeyValueTag),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnKeyValueTags),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::AddRequiredKeyValueTag),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::RemoveItemKeyValueTags),
    AdaptPassThrough(IClientUGCMap::AddItemKeyValueTag),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::RemoveItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
    AdaptPassThrough(IClientUGCMap::BInitWorkshopForGameServer),
    AdaptPassThrough(IClientUGCMap::SuspendDownloads),
    AdaptPassThrough(IClientUGCMap::StartPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTrackingForAllItems),
};
AdaptDeclare(ISteamUGC009);
AdaptDefine(ISteamUGC009, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION009") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumKeyValueTags),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCKeyValueTag),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnOnlyIDs),
    AdaptPassThrough(IClientUGCMap::SetReturnKeyValueTags),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::AddRequiredKeyValueTag),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::RemoveItemKeyValueTags),
    AdaptPassThrough(IClientUGCMap::AddItemKeyValueTag),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::RemoveItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
    AdaptPassThrough(IClientUGCMap::BInitWorkshopForGameServer),
    AdaptPassThrough(IClientUGCMap::SuspendDownloads),
    AdaptPassThrough(IClientUGCMap::StartPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTrackingForAllItems),
};
AdaptDeclare(ISteamUGC010);
AdaptDefine(ISteamUGC010, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION010") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumKeyValueTags),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCKeyValueTag),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnOnlyIDs),
    AdaptPassThrough(IClientUGCMap::SetReturnKeyValueTags),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetReturnPlaytimeStats),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::AddRequiredKeyValueTag),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::RemoveItemKeyValueTags),
    AdaptPassThrough(IClientUGCMap::AddItemKeyValueTag),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::RemoveItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
    AdaptPassThrough(IClientUGCMap::BInitWorkshopForGameServer),
    AdaptPassThrough(IClientUGCMap::SuspendDownloads),
    AdaptPassThrough(IClientUGCMap::StartPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTrackingForAllItems),
    AdaptPassThrough(IClientUGCMap::AddDependency),
    AdaptPassThrough(IClientUGCMap::RemoveDependency),
    AdaptPassThrough(IClientUGCMap::AddAppDependency),
    AdaptPassThrough(IClientUGCMap::RemoveAppDependency),
    AdaptPassThrough(IClientUGCMap::GetAppDependencies),
    AdaptPassThrough(IClientUGCMap::DeleteItem),
};
AdaptDeclare(ISteamUGC011);
AdaptDefine(ISteamUGC011, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION011") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumKeyValueTags),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCKeyValueTag),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnOnlyIDs),
    AdaptPassThrough(IClientUGCMap::SetReturnKeyValueTags),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetReturnPlaytimeStats),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::AddRequiredKeyValueTag),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SetAllowLegacyUpload),
    AdaptPassThrough(IClientUGCMap::RemoveItemKeyValueTags),
    AdaptPassThrough(IClientUGCMap::AddItemKeyValueTag),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::RemoveItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
    AdaptPassThrough(IClientUGCMap::BInitWorkshopForGameServer),
    AdaptPassThrough(IClientUGCMap::SuspendDownloads),
    AdaptPassThrough(IClientUGCMap::StartPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTrackingForAllItems),
    AdaptPassThrough(IClientUGCMap::AddDependency),
    AdaptPassThrough(IClientUGCMap::RemoveDependency),
    AdaptPassThrough(IClientUGCMap::AddAppDependency),
    AdaptPassThrough(IClientUGCMap::RemoveAppDependency),
    AdaptPassThrough(IClientUGCMap::GetAppDependencies),
    AdaptPassThrough(IClientUGCMap::DeleteItem),
};
AdaptDeclare(ISteamUGC012);
AdaptDefine(ISteamUGC012, IClientUGCMap, "STEAMUGC_INTERFACE_VERSION012") = {
    AdaptPassThrough(IClientUGCMap::CreateQueryUserUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, unsigned int), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptOverload(unknown_ret (IClientUGCMap::*)(EUGCQuery, EUGCMatchingUGCType, unsigned int, unsigned int, const char *), IClientUGCMap::CreateQueryAllUGCRequest),
    AdaptPassThrough(IClientUGCMap::CreateQueryUGCDetailsRequest),
    AdaptPassThrough(IClientUGCMap::SendQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCResult),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCPreviewURL),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCMetadata),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCChildren),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCStatistic),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCAdditionalPreview),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCNumKeyValueTags),
    AdaptPassThrough(IClientUGCMap::GetQueryUGCKeyValueTag),
    AdaptPassThrough(IClientUGCMap::ReleaseQueryUGCRequest),
    AdaptPassThrough(IClientUGCMap::AddRequiredTag),
    AdaptPassThrough(IClientUGCMap::AddExcludedTag),
    AdaptPassThrough(IClientUGCMap::SetReturnOnlyIDs),
    AdaptPassThrough(IClientUGCMap::SetReturnKeyValueTags),
    AdaptPassThrough(IClientUGCMap::SetReturnLongDescription),
    AdaptPassThrough(IClientUGCMap::SetReturnMetadata),
    AdaptPassThrough(IClientUGCMap::SetReturnChildren),
    AdaptPassThrough(IClientUGCMap::SetReturnAdditionalPreviews),
    AdaptPassThrough(IClientUGCMap::SetReturnTotalOnly),
    AdaptPassThrough(IClientUGCMap::SetReturnPlaytimeStats),
    AdaptPassThrough(IClientUGCMap::SetLanguage),
    AdaptPassThrough(IClientUGCMap::SetAllowCachedResponse),
    AdaptPassThrough(IClientUGCMap::SetCloudFileNameFilter),
    AdaptPassThrough(IClientUGCMap::SetMatchAnyTag),
    AdaptPassThrough(IClientUGCMap::SetSearchText),
    AdaptPassThrough(IClientUGCMap::SetRankedByTrendDays),
    AdaptPassThrough(IClientUGCMap::AddRequiredKeyValueTag),
    AdaptPassThrough(IClientUGCMap::RequestUGCDetails),
    AdaptPassThrough(IClientUGCMap::CreateItem),
    AdaptPassThrough(IClientUGCMap::StartItemUpdate),
    AdaptPassThrough(IClientUGCMap::SetItemTitle),
    AdaptPassThrough(IClientUGCMap::SetItemDescription),
    AdaptPassThrough(IClientUGCMap::SetItemUpdateLanguage),
    AdaptPassThrough(IClientUGCMap::SetItemMetadata),
    AdaptPassThrough(IClientUGCMap::SetItemVisibility),
    AdaptPassThrough(IClientUGCMap::SetItemTags),
    AdaptPassThrough(IClientUGCMap::SetItemContent),
    AdaptPassThrough(IClientUGCMap::SetItemPreview),
    AdaptPassThrough(IClientUGCMap::SetAllowLegacyUpload),
    AdaptPassThrough(IClientUGCMap::RemoveItemKeyValueTags),
    AdaptPassThrough(IClientUGCMap::AddItemKeyValueTag),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::AddItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewFile),
    AdaptPassThrough(IClientUGCMap::UpdateItemPreviewVideo),
    AdaptPassThrough(IClientUGCMap::RemoveItemPreview),
    AdaptPassThrough(IClientUGCMap::SubmitItemUpdate),
    AdaptPassThrough(IClientUGCMap::GetItemUpdateProgress),
    AdaptPassThrough(IClientUGCMap::SetUserItemVote),
    AdaptPassThrough(IClientUGCMap::GetUserItemVote),
    AdaptPassThrough(IClientUGCMap::AddItemToFavorites),
    AdaptPassThrough(IClientUGCMap::RemoveItemFromFavorites),
    AdaptPassThrough(IClientUGCMap::SubscribeItem),
    AdaptPassThrough(IClientUGCMap::UnsubscribeItem),
    AdaptPassThrough(IClientUGCMap::GetNumSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetSubscribedItems),
    AdaptPassThrough(IClientUGCMap::GetItemState),
    AdaptPassThrough(IClientUGCMap::GetItemInstallInfo),
    AdaptPassThrough(IClientUGCMap::GetItemDownloadInfo),
    AdaptPassThrough(IClientUGCMap::DownloadItem),
    AdaptPassThrough(IClientUGCMap::BInitWorkshopForGameServer),
    AdaptPassThrough(IClientUGCMap::SuspendDownloads),
    AdaptPassThrough(IClientUGCMap::StartPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTracking),
    AdaptPassThrough(IClientUGCMap::StopPlaytimeTrackingForAllItems),
    AdaptPassThrough(IClientUGCMap::AddDependency),
    AdaptPassThrough(IClientUGCMap::RemoveDependency),
    AdaptPassThrough(IClientUGCMap::AddAppDependency),
    AdaptPassThrough(IClientUGCMap::RemoveAppDependency),
    AdaptPassThrough(IClientUGCMap::GetAppDependencies),
    AdaptPassThrough(IClientUGCMap::DeleteItem),
};
