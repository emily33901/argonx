
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientMusic.h"
}

template <bool isServer>
class ClientMusic : public Reference::IClientMusic {
public:
    UserHandle userHandle;
    ClientMusic(UserHandle h) : userHandle(h) {}

    unknown_ret BIsEnabled() override {
        return unknown_ret();
    }
    unknown_ret Enable(bool) override {
        return unknown_ret();
    }
    unknown_ret EnableCrawlLogging(bool) override {
        return unknown_ret();
    }
    unknown_ret BIsPlaying() override {
        return unknown_ret();
    }
    unknown_ret GetQueueCount() override {
        return unknown_ret();
    }
    unknown_ret GetCurrentQueueEntry() override {
        return unknown_ret();
    }
    unknown_ret GetQueueEntryURI(int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetQueueEntryData(int, char *, int, char *, int, char *, int, int *, ETrackQueueOrigin *, int *) override {
        return unknown_ret();
    }
    unknown_ret GetQueueEntryOrigin(int, ETrackQueueOrigin *, int *) override {
        return unknown_ret();
    }
    unknown_ret EmptyQueue() override {
        return unknown_ret();
    }
    unknown_ret RemoveQueueEntry(int, bool) override {
        return unknown_ret();
    }
    unknown_ret AddArtistToQueue(char const *, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret AddTracksOfAlbumIDToQueue(int, int, bool, char const *, bool, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret AddAllTracksOfAlbumIDToQueue(int, int, bool, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret AddTracksOfPlaylistIDToQueue(int, int, bool, bool, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret SetSuppressAutoTrackAdvance(bool) override {
        return unknown_ret();
    }
    unknown_ret GetPlaybackStatus() override {
        return unknown_ret();
    }
    unknown_ret SetPlayingRepeatStatus(PlayingRepeat_Status) override {
        return unknown_ret();
    }
    unknown_ret GetPlayingRepeatStatus() override {
        return unknown_ret();
    }
    unknown_ret TogglePlayingRepeatStatus() override {
        return unknown_ret();
    }
    unknown_ret SetPlayingShuffled(bool) override {
        return unknown_ret();
    }
    unknown_ret IsPlayingShuffled() override {
        return unknown_ret();
    }
    unknown_ret Play() override {
        return unknown_ret();
    }
    unknown_ret Pause() override {
        return unknown_ret();
    }
    unknown_ret PlayPrevious() override {
        return unknown_ret();
    }
    unknown_ret PlayNext() override {
        return unknown_ret();
    }
    unknown_ret PlayEntry(int) override {
        return unknown_ret();
    }
    unknown_ret TogglePlayPause() override {
        return unknown_ret();
    }
    unknown_ret SetVolume(float) override {
        return unknown_ret();
    }
    unknown_ret GetVolume() override {
        return unknown_ret();
    }
    unknown_ret ToggleMuteVolume() override {
        return unknown_ret();
    }
    unknown_ret IncreaseVolume() override {
        return unknown_ret();
    }
    unknown_ret DecreaseVolume() override {
        return unknown_ret();
    }
    unknown_ret SetPlaybackPosition(int) override {
        return unknown_ret();
    }
    unknown_ret GetPlaybackPosition() override {
        return unknown_ret();
    }
    unknown_ret GetPlaybackDuration() override {
        return unknown_ret();
    }
    unknown_ret LocalLibraryCrawlTrack(char const *) override {
        return unknown_ret();
    }
    unknown_ret ResetLocalLibrary() override {
        return unknown_ret();
    }
    unknown_ret GetStatusLocalLibrary() override {
        return unknown_ret();
    }
    unknown_ret SaveLocalLibraryDirectorySettings() override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryDirectoryEntryCount() override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryDirectoryEntry(int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret AddLocalLibraryDirectoryEntry(char const *) override {
        return unknown_ret();
    }
    unknown_ret ResetLocalLibraryDirectories(bool) override {
        return unknown_ret();
    }
    unknown_ret GetDefaultLocalLibraryDirectory(char *, int) override {
        return unknown_ret();
    }
    unknown_ret LocalLibraryStopCrawling() override {
        return unknown_ret();
    }
    unknown_ret UpdateLocalLibraryDirectoriesToCrawl() override {
        return unknown_ret();
    }
    unknown_ret BLocalLibraryIsCrawling() override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryTrackCount() override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumCount() override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumID(int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumIDEntry(int, char *, int, char *, int, int *, int *, bool *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumIDTrackEntry(int, int, char *, int, int *, char *, int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumDirectoryForAlbumID(int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumSortNameForAlbumID(int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryArtistSortNameForAlbumID(int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryTrackCountForAlbumID(int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumIDTrackKey(int, int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumIDForTrackKey(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryArtistCount() override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryArtistName(int, char *, int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumCountForArtistName(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryTrackAndAlbumCountOfArtistName(char const *, int *, int *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryAlbumIDForArtist(char const *, int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryRepresentativeAlbumIDForArtist(char const *, bool *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryTrackEntry(char const *, char *, int, int *, char *, int) override {
        return unknown_ret();
    }
    unknown_ret BRequestAllArtistListData(int) override {
        return unknown_ret();
    }
    unknown_ret BRequestAllAlbumListData(int) override {
        return unknown_ret();
    }
    unknown_ret BRequestAllTracksListDataForAlbumID(int, int) override {
        return unknown_ret();
    }
    unknown_ret GetPlaylistCount() override {
        return unknown_ret();
    }
    unknown_ret GetPlaylistID(int) override {
        return unknown_ret();
    }
    unknown_ret GetPositionForPlaylistID(int) override {
        return unknown_ret();
    }
    unknown_ret GetPlaylistIDForPosition(int) override {
        return unknown_ret();
    }
    unknown_ret BRequestAllPlayListData(int) override {
        return unknown_ret();
    }
    unknown_ret GetNextPlaylistName(char const *, char *, int) override {
        return unknown_ret();
    }
    unknown_ret InsertPlaylistWithNameAtPosition(char const *, int) override {
        return unknown_ret();
    }
    unknown_ret MovePlaylistFromPositionToPosition(int, int) override {
        return unknown_ret();
    }
    unknown_ret DeletePlaylistWithID(int) override {
        return unknown_ret();
    }
    unknown_ret RenamePlaylistWithID(int, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddRandomTracksToPlaylistID(int, int) override {
        return unknown_ret();
    }
    unknown_ret GetPlaylistIDData(int, char *, int, int *, int *, int *, int *, int *) override {
        return unknown_ret();
    }
    unknown_ret GetPlaylistIDTrackCount(int) override {
        return unknown_ret();
    }
    unknown_ret BRequestAllTracksListDataForPlaylistID(int, int) override {
        return unknown_ret();
    }
    unknown_ret GetPlaylistIDTrackKey(int, int, char *, int, int *) override {
        return unknown_ret();
    }
    unknown_ret GetPositionForPlaylistItemID(int) override {
        return unknown_ret();
    }
    unknown_ret AddTrackKeyToPlaylistID(int, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddAlbumIDToPlaylistID(int, int, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddArtistNameToPlaylistID(int, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddPlaylistIDToPlaylistID(int, int) override {
        return unknown_ret();
    }
    unknown_ret RemovePlaylistPositionFromPlaylistID(int, int) override {
        return unknown_ret();
    }
    unknown_ret RemoveAllTracksFromPlaylistID(int, bool) override {
        return unknown_ret();
    }
    unknown_ret MoveTrackFromPositionToPositonInPlaylistID(int, int, int) override {
        return unknown_ret();
    }
    unknown_ret AppendQueueToPlaylistID(int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetLocalLibraryRepresentativeAlbumIDForPlaylist(int, bool *) override {
        return unknown_ret();
    }
    unknown_ret MarkTrackKeyAsPlayed(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetMostRecentlyPlayedAlbums(int, int *) override {
        return unknown_ret();
    }
    unknown_ret GetMostRecentlyAddedAlbums(int, int *) override {
        return unknown_ret();
    }
    unknown_ret ActivateRemotePlayerWithID(int) override {
        return unknown_ret();
    }
    unknown_ret GetActiveRemotePlayerID() override {
        return unknown_ret();
    }
    unknown_ret GetRemotePlayerCount() override {
        return unknown_ret();
    }
    unknown_ret GetRemotePlayerIDAndName(int, int *, char *, int) override {
        return unknown_ret();
    }
    unknown_ret GetCurrentEntryTextForRemotePlayerWithID(int, char *, int) override {
        return unknown_ret();
    }
    unknown_ret RegisterSteamMusicRemote(char const *) override {
        return unknown_ret();
    }
    unknown_ret DeregisterSteamMusicRemote() override {
        return unknown_ret();
    }
    unknown_ret BIsCurrentMusicRemote() override {
        return unknown_ret();
    }
    unknown_ret BActivationSuccess(bool) override {
        return unknown_ret();
    }
    unknown_ret SetDisplayName(char const *) override {
        return unknown_ret();
    }
    unknown_ret SetPNGIcon_64x64(void *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret EnablePlayPrevious(bool) override {
        return unknown_ret();
    }
    unknown_ret EnablePlayNext(bool) override {
        return unknown_ret();
    }
    unknown_ret EnableShuffled(bool) override {
        return unknown_ret();
    }
    unknown_ret EnableLooped(bool) override {
        return unknown_ret();
    }
    unknown_ret EnableQueue(bool) override {
        return unknown_ret();
    }
    unknown_ret EnablePlaylists(bool) override {
        return unknown_ret();
    }
    unknown_ret UpdatePlaybackStatus(AudioPlayback_Status) override {
        return unknown_ret();
    }
    unknown_ret UpdateShuffled(bool) override {
        return unknown_ret();
    }
    unknown_ret UpdateLooped(bool) override {
        return unknown_ret();
    }
    unknown_ret UpdateVolume(float) override {
        return unknown_ret();
    }
    unknown_ret CurrentEntryWillChange() override {
        return unknown_ret();
    }
    unknown_ret CurrentEntryIsAvailable(bool) override {
        return unknown_ret();
    }
    unknown_ret UpdateCurrentEntryText(char const *) override {
        return unknown_ret();
    }
    unknown_ret UpdateCurrentEntryElapsedSeconds(int) override {
        return unknown_ret();
    }
    unknown_ret UpdateCurrentEntryCoverArt(void *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CurrentEntryDidChange() override {
        return unknown_ret();
    }
    unknown_ret QueueWillChange() override {
        return unknown_ret();
    }
    unknown_ret ResetQueueEntries() override {
        return unknown_ret();
    }
    unknown_ret SetQueueEntry(int, int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetCurrentQueueEntry(int) override {
        return unknown_ret();
    }
    unknown_ret QueueDidChange() override {
        return unknown_ret();
    }
    unknown_ret PlaylistWillChange() override {
        return unknown_ret();
    }
    unknown_ret ResetPlaylistEntries() override {
        return unknown_ret();
    }
    unknown_ret SetPlaylistEntry(int, int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetCurrentPlaylistEntry(int) override {
        return unknown_ret();
    }
    unknown_ret PlaylistDidChange() override {
        return unknown_ret();
    }
    unknown_ret RequestAlbumCoverForAlbumID(int) override {
        return unknown_ret();
    }
    unknown_ret RequestAlbumCoverForTrackKey(char const *) override {
        return unknown_ret();
    }
    unknown_ret GetAlbumCoverForIndex(int, void *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CancelAlbumCoverRequestForIndex(int) override {
        return unknown_ret();
    }
    unknown_ret GetAlbumCoverURLForAlbumID(int, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAlbumCoverURLForTrackKey(char const *, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret StartUsingSpotify() override {
        return unknown_ret();
    }
    unknown_ret StopUsingSpotify() override {
        return unknown_ret();
    }
    unknown_ret GetStatusSpotify() override {
        return unknown_ret();
    }
    unknown_ret LoginSpotify(char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret ReloginSpotify() override {
        return unknown_ret();
    }
    unknown_ret GetCurrentUserSpotify() override {
        return unknown_ret();
    }
    unknown_ret ForgetCurrentUserSpotify() override {
        return unknown_ret();
    }
    unknown_ret LogoutSpotify() override {
        return unknown_ret();
    }
    unknown_ret DumpStatusToConsole() override {
        return unknown_ret();
    }
    unknown_ret ReplacePlaylistWithSoundtrackAlbum(unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientMusic, "SteamMusic");

using IClientMusic = ClientMusic<false>;

AdaptDeclare(ISteamMusic001);
AdaptDefine(ISteamMusic001, IClientMusic, "SteamMusic001") = {
    AdaptPassThrough(IClientMusic::BIsEnabled),
    AdaptPassThrough(IClientMusic::BIsPlaying),
    AdaptPassThrough(IClientMusic::GetPlaybackStatus),
    AdaptPassThrough(IClientMusic::Play),
    AdaptPassThrough(IClientMusic::Pause),
    AdaptPassThrough(IClientMusic::PlayPrevious),
    AdaptPassThrough(IClientMusic::PlayNext),
    AdaptPassThrough(IClientMusic::SetVolume),
    AdaptPassThrough(IClientMusic::GetVolume),
};
AdaptDeclare(ISteamMusicRemote001);
AdaptDefine(ISteamMusicRemote001, IClientMusic, "SteamMusicRemote001") = {
    AdaptPassThrough(IClientMusic::RegisterSteamMusicRemote),
    AdaptPassThrough(IClientMusic::DeregisterSteamMusicRemote),
    AdaptPassThrough(IClientMusic::BIsCurrentMusicRemote),
    AdaptPassThrough(IClientMusic::BActivationSuccess),
    AdaptPassThrough(IClientMusic::SetDisplayName),
    AdaptPassThrough(IClientMusic::SetPNGIcon_64x64),
    AdaptPassThrough(IClientMusic::EnablePlayPrevious),
    AdaptPassThrough(IClientMusic::EnablePlayNext),
    AdaptPassThrough(IClientMusic::EnableShuffled),
    AdaptPassThrough(IClientMusic::EnableLooped),
    AdaptPassThrough(IClientMusic::EnableQueue),
    AdaptPassThrough(IClientMusic::EnablePlaylists),
    AdaptPassThrough(IClientMusic::UpdatePlaybackStatus),
    AdaptPassThrough(IClientMusic::UpdateShuffled),
    AdaptPassThrough(IClientMusic::UpdateLooped),
    AdaptPassThrough(IClientMusic::UpdateVolume),
    AdaptPassThrough(IClientMusic::CurrentEntryWillChange),
    AdaptPassThrough(IClientMusic::CurrentEntryIsAvailable),
    AdaptPassThrough(IClientMusic::UpdateCurrentEntryText),
    AdaptPassThrough(IClientMusic::UpdateCurrentEntryElapsedSeconds),
    AdaptPassThrough(IClientMusic::UpdateCurrentEntryCoverArt),
    AdaptPassThrough(IClientMusic::CurrentEntryDidChange),
    AdaptPassThrough(IClientMusic::QueueWillChange),
    AdaptPassThrough(IClientMusic::ResetQueueEntries),
    AdaptPassThrough(IClientMusic::SetQueueEntry),
    AdaptPassThrough(IClientMusic::SetCurrentQueueEntry),
    AdaptPassThrough(IClientMusic::QueueDidChange),
    AdaptPassThrough(IClientMusic::PlaylistWillChange),
    AdaptPassThrough(IClientMusic::ResetPlaylistEntries),
    AdaptPassThrough(IClientMusic::SetPlaylistEntry),
    AdaptPassThrough(IClientMusic::SetCurrentPlaylistEntry),
    AdaptPassThrough(IClientMusic::PlaylistDidChange),
};
