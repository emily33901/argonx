
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientVideo.h"
}

template <bool isServer>
class ClientVideo : public Reference::IClientVideo {
public:
    UserHandle userHandle;
    ClientVideo(UserHandle h) : userHandle(h) {}

    unknown_ret BGetUserVideoFolder(char *, int) override {
        return unknown_ret();
    }
    unknown_ret UnlockH264() override {
        return unknown_ret();
    }
    unknown_ret EGetBroadcastReady() override {
        return unknown_ret();
    }
    unknown_ret BeginBroadcastSession() override {
        return unknown_ret();
    }
    unknown_ret EndBroadcastSession() override {
        return unknown_ret();
    }
    unknown_ret IsBroadcasting(int *) override {
        return unknown_ret();
    }
    unknown_ret BIsUploadingThumbnails() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastSessionID() override {
        return unknown_ret();
    }
    unknown_ret ReceiveBroadcastChat(CSteamID, unsigned long long, bool) override {
        return unknown_ret();
    }
    unknown_ret PostBroadcastChat(unsigned long long, char const *) override {
        return unknown_ret();
    }
    unknown_ret MuteBroadcastChatUser(unsigned long long, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret InitBroadcastVideo(int, int, int, int, unsigned char const *, int, unsigned char const *, int) override {
        return unknown_ret();
    }
    unknown_ret InitBroadcastAudio(int, int, int, int, int, unsigned char const *, int) override {
        return unknown_ret();
    }
    unknown_ret UploadBroadcastFrame(bool, bool, unsigned int, long long, long long, unsigned char const *, int) override {
        return unknown_ret();
    }
    unknown_ret UploadBroadcastThumbnail(int, int, unsigned char const *, int) override {
        return unknown_ret();
    }
    unknown_ret DroppedVideoFrames(int) override {
        return unknown_ret();
    }
    unknown_ret SetCurrentVideoEncodingRate(int) override {
        return unknown_ret();
    }
    unknown_ret SetMicrophoneState(bool, bool) override {
        return unknown_ret();
    }
    unknown_ret SetVideoSource(bool) override {
        return unknown_ret();
    }
    unknown_ret BroadcastRecorderError(EBroadcastRecorderResult) override {
        return unknown_ret();
    }
    unknown_ret LoadBroadcastSettings() override {
        return unknown_ret();
    }
    unknown_ret SetBroadcastPermissions(EBroadcastPermission) override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastPermissions() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastMaxKbps() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastDelaySeconds() override {
        return unknown_ret();
    }
    unknown_ret BGetBroadcastDimensions(int *, int *) override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastIncludeDesktop() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastRecordSystemAudio() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastRecordMic() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastShowChatCorner() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastShowDebugInfo() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastShowReminderBanner() override {
        return unknown_ret();
    }
    unknown_ret GetBroadcastEncoderSetting() override {
        return unknown_ret();
    }
    unknown_ret InviteToBroadcast(CSteamID, bool, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IgnoreApprovalRequest(CSteamID, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BroadcastFirstTimeComplete() override {
        return unknown_ret();
    }
    unknown_ret SetInHomeStreamState(bool) override {
        return unknown_ret();
    }
    unknown_ret WatchBroadcast(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetWatchBroadcastMPD(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetApprovalRequestCount() override {
        return unknown_ret();
    }
    unknown_ret GetApprovalRequests(CSteamID *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AddBroadcastGameData(char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret RemoveBroadcastGameData(char const *) override {
        return unknown_ret();
    }
    unknown_ret AddTimelineMarker(char const *, bool, unsigned char, unsigned char, unsigned char) override {
        return unknown_ret();
    }
    unknown_ret RemoveTimelineMarker() override {
        return unknown_ret();
    }
    unknown_ret AddRegion(char const *, char const *, SteamTVRegion_t const *, ESteamTVRegionBehavior) override {
        return unknown_ret();
    }
    unknown_ret RemoveRegion(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetVideoURL(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetOPFSettings(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetOPFStringForApp(unsigned int, char *, int, int *) override {
        return unknown_ret();
    }
    unknown_ret WebRTCGetTURNAddress(CUtlString *) override {
        return unknown_ret();
    }
    unknown_ret WebRTCStartResult(unsigned long long, bool, char const *) override {
        return unknown_ret();
    }
    unknown_ret WebRTCAddCandidate(unsigned long long, char const *, int, char const *) override {
        return unknown_ret();
    }
    unknown_ret WebRTCGetAnswer(unsigned long long, CUtlString *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientVideo, "SteamVideo");

using IClientVideo = ClientVideo<false>;

AdaptDeclare(ISteamVideo001);
AdaptDefine(ISteamVideo001, IClientVideo, "SteamVideo001") = {
    AdaptPassThrough(IClientVideo::GetVideoURL),
    AdaptPassThrough(IClientVideo::IsBroadcasting),
};
AdaptDeclare(ISteamVideo002);
AdaptDefine(ISteamVideo002, IClientVideo, "SteamVideo002") = {
    AdaptPassThrough(IClientVideo::GetVideoURL),
    AdaptPassThrough(IClientVideo::IsBroadcasting),
    AdaptPassThrough(IClientVideo::GetOPFSettings),
    AdaptPassThrough(IClientVideo::GetOPFStringForApp),
};
