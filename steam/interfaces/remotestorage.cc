#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientRemoteStorage.h"
}

template <bool isServer>
class ClientRemoteStorageMap : public Reference::IClientRemoteStorage {
public:
    ClientRemoteStorageMap(UserHandle h) {}

    // Inherited via IClientRemoteStorage
    virtual unknown_ret FileWrite(unsigned int, ERemoteStorageFileRoot, char const *, void const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFileSize(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileWriteAsync(unsigned int, ERemoteStorageFileRoot, char const *, CUtlBuffer *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileReadAsync(unsigned int, ERemoteStorageFileRoot, char const *, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret FileReadAsyncComplete(unsigned int, unsigned long long, void *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret FileRead(unsigned int, ERemoteStorageFileRoot, char const *, void *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret FileForget(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileDelete(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileShare(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileExists(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FilePersisted(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFileTimestamp(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSyncPlatforms(unsigned int, ERemoteStorageFileRoot, char const *, ERemoteStoragePlatform) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSyncPlatforms(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileWriteStreamOpen(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileWriteStreamClose(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret FileWriteStreamCancel(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret FileWriteStreamWriteChunk(unsigned long long, void const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFileCount(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetFileNameAndSize(unsigned int, int, ERemoteStorageFileRoot *, int *, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetQuota(unsigned int, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret IsCloudEnabledForAccount() override {
        return unknown_ret();
    }
    virtual unknown_ret IsCloudEnabledForApp(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetCloudEnabledForApp(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret UGCDownload(unsigned long long, bool, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret UGCDownloadToLocation(unsigned long long, char const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUGCDownloadProgress(unsigned long long, int *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUGCDetails(unsigned long long, unsigned int *, char **, int *, CSteamID *) override {
        return unknown_ret();
    }
    virtual unknown_ret UGCRead(unsigned long long, void *, int, unsigned int, EUGCReadAction) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCachedUGCCount() override {
        return unknown_ret();
    }
    virtual unknown_ret GetCachedUGCHandle(int) override {
        return unknown_ret();
    }
    virtual unknown_ret PublishFile(unsigned int, ERemoteStorageFileRoot, char const *, char const *, unsigned int, char const *, char const *, ERemoteStoragePublishedFileVisibility, SteamParamStringArray_t const *, EWorkshopFileType) override {
        return unknown_ret();
    }
    virtual unknown_ret PublishVideo(unsigned int, EWorkshopVideoProvider, char const *, char const *, ERemoteStorageFileRoot, char const *, unsigned int, char const *, char const *, ERemoteStoragePublishedFileVisibility, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    virtual unknown_ret PublishVideoFromURL(unsigned int, ERemoteStorageFileRoot, char const *, char const *, unsigned int, char const *, char const *, ERemoteStoragePublishedFileVisibility, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    virtual unknown_ret CreatePublishedFileUpdateRequest(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileFile(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFilePreviewFile(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileTitle(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileDescription(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileSetChangeDescription(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileVisibility(unsigned long long, ERemoteStoragePublishedFileVisibility) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileTags(unsigned long long, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdatePublishedFileURL(unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret CommitPublishedFileUpdate(unsigned int, ERemoteStorageFileRoot, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetPublishedFileDetails(unsigned long long, bool, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret DeletePublishedFile(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateUserPublishedFiles(unsigned int, unsigned int, ERemoteStoragePublishedFileSortOrder) override {
        return unknown_ret();
    }
    virtual unknown_ret SubscribePublishedFile(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateUserSubscribedFiles(unsigned int, unsigned int, unsigned char, EPublishedFileInfoMatchingFileType) override {
        return unknown_ret();
    }
    virtual unknown_ret UnsubscribePublishedFile(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret SetUserPublishedFileAction(unsigned int, unsigned long long, EWorkshopFileAction) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumeratePublishedFilesByUserAction(unsigned int, EWorkshopFileAction, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateUserSubscribedFilesWithUpdates(unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCREItemVoteSummary(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdateUserPublishedItemVote(unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserPublishedItemVoteDetails(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateUserSharedWorkshopFiles(unsigned int, CSteamID, unsigned int, SteamParamStringArray_t const *, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumeratePublishedWorkshopFiles(unsigned int, EWorkshopEnumerationType, EPublishedFileInfoMatchingFileType, unsigned int, unsigned int, unsigned int, SteamParamStringArray_t const *, SteamParamStringArray_t const *) override {
        return unknown_ret();
    }
    virtual unknown_ret EGetFileSyncState(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsFileSyncing(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FilePersist(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FileFetch(unsigned int, ERemoteStorageFileRoot, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ResolvePath(unsigned int, ERemoteStorageFileRoot, char const *, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret FileTouch(unsigned int, ERemoteStorageFileRoot, char const *, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetCloudEnabledForAccount(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret LoadLocalFileInfoCache(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret EvaluateRemoteStorageSyncState(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetRemoteStorageSyncState(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret HaveLatestFilesLocally(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConflictingFileTimestamps(unsigned int, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret ResolveSyncConflict(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SynchronizeApp(unsigned int, bool, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IsAppSyncInProgress(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RunAutoCloudOnAppLaunch(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RunAutoCloudOnAppExit(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ResetFileRequestState(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearPublishFileUpdateRequests(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSubscribedFileDownloadCount() override {
        return unknown_ret();
    }
    virtual unknown_ret BGetSubscribedFileDownloadInfo(int, unsigned long long *, unsigned int *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetSubscribedFileDownloadInfo(unsigned long long, unsigned int *, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret PauseSubscribedFileDownloadsForApp(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ResumeSubscribedFileDownloadsForApp(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret PauseAllSubscribedFileDownloads() override {
        return unknown_ret();
    }
    virtual unknown_ret ResumeAllSubscribedFileDownloads() override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientRemoteStorageMap, "SteamRemoteStorage");

using IClientRemoteStorageMap = ClientRemoteStorageMap<false>;

AdaptDeclare(ISteamRemoteStorage001);
AdaptDefine(ISteamRemoteStorage001, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION001") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
};
AdaptDeclare(ISteamRemoteStorage002);
AdaptDefine(ISteamRemoteStorage002, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION002") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
};
AdaptDeclare(ISteamRemoteStorage003);
AdaptDefine(ISteamRemoteStorage003, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION003") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
};
AdaptDeclare(ISteamRemoteStorage004);
AdaptDefine(ISteamRemoteStorage004, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION004") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
};
AdaptDeclare(ISteamRemoteStorage005);
AdaptDefine(ISteamRemoteStorage005, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION005") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptPassThrough(IClientRemoteStorageMap::PublishFile),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptEmpty(IClientRemoteStorageMap::UpdatePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
};
AdaptDeclare(ISteamRemoteStorage006);
AdaptDefine(ISteamRemoteStorage006, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION006") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
};
AdaptDeclare(ISteamRemoteStorage007);
AdaptDefine(ISteamRemoteStorage007, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION007") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
};
AdaptDeclare(ISteamRemoteStorage008);
AdaptDefine(ISteamRemoteStorage008, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION008") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
};
AdaptDeclare(ISteamRemoteStorage009);
AdaptDefine(ISteamRemoteStorage009, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION009") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
};
AdaptDeclare(ISteamRemoteStorage010);
AdaptDefine(ISteamRemoteStorage010, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION010") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownloadToLocation),
};
AdaptDeclare(ISteamRemoteStorage011);
AdaptDefine(ISteamRemoteStorage011, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION011") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownloadToLocation),
};
AdaptDeclare(ISteamRemoteStorage012);
AdaptDefine(ISteamRemoteStorage012, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION012") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownloadToLocation),
};
AdaptDeclare(ISteamRemoteStorage013);
AdaptDefine(ISteamRemoteStorage013, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION013") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteAsync),
    AdaptPassThrough(IClientRemoteStorageMap::FileReadAsync),
    AdaptPassThrough(IClientRemoteStorageMap::FileReadAsyncComplete),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownloadToLocation),
};
AdaptDeclare(ISteamRemoteStorage014);
AdaptDefine(ISteamRemoteStorage014, IClientRemoteStorageMap, "STEAMREMOTESTORAGE_INTERFACE_VERSION014") = {
    AdaptPassThrough(IClientRemoteStorageMap::FileWrite),
    AdaptPassThrough(IClientRemoteStorageMap::FileRead),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteAsync),
    AdaptPassThrough(IClientRemoteStorageMap::FileReadAsync),
    AdaptPassThrough(IClientRemoteStorageMap::FileReadAsyncComplete),
    AdaptPassThrough(IClientRemoteStorageMap::FileForget),
    AdaptPassThrough(IClientRemoteStorageMap::FileDelete),
    AdaptPassThrough(IClientRemoteStorageMap::FileShare),
    AdaptPassThrough(IClientRemoteStorageMap::SetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamOpen),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamWriteChunk),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamClose),
    AdaptPassThrough(IClientRemoteStorageMap::FileWriteStreamCancel),
    AdaptPassThrough(IClientRemoteStorageMap::FileExists),
    AdaptPassThrough(IClientRemoteStorageMap::FilePersisted),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileTimestamp),
    AdaptPassThrough(IClientRemoteStorageMap::GetSyncPlatforms),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetFileNameAndSize),
    AdaptPassThrough(IClientRemoteStorageMap::GetQuota),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForAccount),
    AdaptPassThrough(IClientRemoteStorageMap::IsCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::SetCloudEnabledForApp),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownload),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDownloadProgress),
    AdaptPassThrough(IClientRemoteStorageMap::GetUGCDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UGCRead),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCCount),
    AdaptPassThrough(IClientRemoteStorageMap::GetCachedUGCHandle),
    AdaptEmpty(IClientRemoteStorageMap::PublishWorkshopFile),
    AdaptPassThrough(IClientRemoteStorageMap::CreatePublishedFileUpdateRequest),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFilePreviewFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTitle),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileDescription),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileVisibility),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileTags),
    AdaptPassThrough(IClientRemoteStorageMap::CommitPublishedFileUpdate),
    AdaptPassThrough(IClientRemoteStorageMap::GetPublishedFileDetails),
    AdaptPassThrough(IClientRemoteStorageMap::DeletePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserPublishedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::SubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSubscribedFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UnsubscribePublishedFile),
    AdaptPassThrough(IClientRemoteStorageMap::UpdatePublishedFileSetChangeDescription),
    AdaptEmpty(IClientRemoteStorageMap::GetPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::UpdateUserPublishedItemVote),
    AdaptPassThrough(IClientRemoteStorageMap::GetUserPublishedItemVoteDetails),
    AdaptPassThrough(IClientRemoteStorageMap::EnumerateUserSharedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::PublishVideo),
    AdaptPassThrough(IClientRemoteStorageMap::SetUserPublishedFileAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedFilesByUserAction),
    AdaptPassThrough(IClientRemoteStorageMap::EnumeratePublishedWorkshopFiles),
    AdaptPassThrough(IClientRemoteStorageMap::UGCDownloadToLocation),
};
