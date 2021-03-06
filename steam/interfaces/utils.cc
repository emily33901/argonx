#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientUtils.h"
}

extern Pipe *clientPipe;

template <bool isServer>
class ClientUtilsMap : public Reference::IClientUtils {
public:
    UserHandle userHandle;
    ClientUtilsMap(UserHandle h) : userHandle(h) {
    }

    // Inherited via IClientUtils
    virtual const char *GetInstallPath() override {
        return "";
    }
    virtual unknown_ret GetUserBaseFolderInstallImage() override {
        return unknown_ret();
    }
    virtual unknown_ret GetManagedContentRoot() override {
        return unknown_ret();
    }
    virtual unknown_ret GetSecondsSinceAppActive() override {
        RpcMakeCallIfClient(GetSecondsSinceAppActive, utils) {
            return 11;
        }
    }
    virtual unknown_ret GetSecondsSinceComputerActive() override {
        return unknown_ret();
    }
    virtual unknown_ret SetComputerActive() override {
        return unknown_ret();
    }
    virtual EUniverse GetConnectedUniverse() override {
        // Its only possible to connect to public universe
        // ... so just pretend that its the only option
        return EUniverse::k_EUniversePublic;
    }
    virtual unknown_ret GetServerRealTime() override {
        // TODO: ask server for time
        return unknown_ret();
    }
    virtual const char *GetIPCountry() override {
        RpcMakeCallIfClient(GetIPCountry, utils) {
            // TODO: implement some form of geolocation here (or maybe ask steam?)
            return "GB";
        }
    }
    virtual unknown_ret GetImageSize(int imgHandle, unsigned int *w, unsigned int *h) override {
        RpcMakeCallIfClient(GetImageSize, utils, imgHandle, w, h) {
            *w = 10;
            *h = 15;
            return unknown_ret();
        }
    }
    virtual unknown_ret GetImageRGBA(int imgHandle, u8 *bufferOut, u32 maxOut) override {
        RpcMakeCallIfClient(GetImageRGBA, utils, imgHandle, bufferOut, maxOut) {
            memset(bufferOut, 0x00, maxOut);

            return maxOut;
        }
    }
    virtual unknown_ret GetCSERIPPort(unsigned int *, unsigned short *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumRunningApps() override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentBatteryPower() override {
        return unknown_ret();
    }
    virtual unknown_ret SetOfflineMode(bool offline) override {
        return unknown_ret();
    }
    virtual unknown_ret GetOfflineMode() override {
        return unknown_ret();
    }
    virtual unknown_ret SetAppIDForCurrentPipe(unsigned int appid, bool trackProcess) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppID() override {
        return unknown_ret();
    }
    virtual unknown_ret SetAPIDebuggingActive(bool a, bool b) override {
        RpcMakeCallIfClient(SetAPIDebuggingActive, utils, a, b) {
            return unknown_ret();
        }
    }
    virtual unknown_ret AllocPendingAPICallHandle() override {
        return unknown_ret();
    }
    virtual bool IsAPICallCompleted(Steam::SteamAPICall_t h, bool *failed) override {
        RpcMakeCallIfClient(IsAPICallCompleted, utils, h, failed) {
            return JobManager::HasResult((i64)h);
        }
    }
    virtual ESteamAPICallFailure GetAPICallFailureReason(Steam::SteamAPICall_t h) override {
        RpcMakeCallIfClient(GetAPICallFailureReason, utils, h) {
            // TODO: we need some method of actually conveying failure to end user!
            return ESteamAPICallFailure::k_ESteamAPICallFailureNone;
        }
    }
    virtual bool GetAPICallResult(Steam::SteamAPICall_t h, u8 *outBuffer, u32 bufferSize, int expectedCallback, bool *failed) override {
        RpcMakeCallIfClient(GetAPICallResult, utils, h, outBuffer, bufferSize, expectedCallback, failed) {

            // If the call isnt ready then early out
            if (!IsAPICallCompleted(h, failed)) return false;

            auto callbackBuffer = JobManager::FetchResult((i64)h);

            // Check the first u32 in the buffer to see if it matches the expected callback
            auto cbId = callbackBuffer.Read<u32>();

            if (cbId != expectedCallback) return false;

            // Copy the buffer into the storage allocated by the user
            callbackBuffer.SetPos(0);
            callbackBuffer.ReadInto<u8, u32>(std::make_pair(outBuffer, bufferSize));

            *failed = false;

            return true;
        }
    }
    virtual unknown_ret SetAPICallResultWithoutPostingCallback(unsigned long long handle, void const *callback, int size, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SignalAppsToShutDown() override {
        return unknown_ret();
    }
    virtual unknown_ret SignalServiceAppsToDisconnect() override {
        return unknown_ret();
    }
    virtual unknown_ret TerminateAllAppsMultiStep(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCellID() override {
        return unknown_ret();
    }
    virtual unknown_ret BIsGlobalInstance() override {
        return unknown_ret();
    }
    virtual unknown_ret CheckFileSignature(char const *filename) override {
        RpcMakeCallIfClient(CheckFileSignature, utils, filename) {

            return strlen(filename);
        }
    }
    unknown_ret GetBuildID() override {
        return unknown_ret();
    }
    unknown_ret SetCurrentUIMode(EUIMode) override {
        return unknown_ret();
    }
    unknown_ret GetCurrentUIMode() override {
        return unknown_ret();
    }
    unknown_ret ShutdownLauncher(bool, bool) override {
        return unknown_ret();
    }
    unknown_ret SetLauncherType(ELauncherType) override {
        return unknown_ret();
    }
    unknown_ret GetLauncherType() override {
        return unknown_ret();
    }
    unknown_ret ShowGamepadTextInput(EGamepadTextInputMode, EGamepadTextInputLineMode, char const *, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetEnteredGamepadTextLength() override {
        return unknown_ret();
    }
    unknown_ret GetEnteredGamepadTextInput(char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GamepadTextInputClosed(int, bool, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetSpew(int, int, int) override {
        return unknown_ret();
    }
    unknown_ret BDownloadsDisabled() override {
        return unknown_ret();
    }
    unknown_ret SetFocusedWindow(CGameID, unsigned long long, bool) override {
        return unknown_ret();
    }
    unknown_ret GetSteamUILanguage() override {
        return unknown_ret();
    }
    unknown_ret CheckSteamReachable() override {
        return unknown_ret();
    }
    unknown_ret SetLastGameLaunchMethod(EGameLaunchMethod) override {
        return unknown_ret();
    }
    unknown_ret SetVideoAdapterInfo(int, int, int, int, int, int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetControllerOverrideMode(CGameID, char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetOverlayWindowFocusForPipe(bool, bool, CGameID) override {
        return unknown_ret();
    }
    unknown_ret GetGameOverlayUIInstanceFocusGameID(bool *) override {
        return unknown_ret();
    }
    unknown_ret SetControllerConfigFileForAppID(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetControllerConfigFileForAppID(unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsSteamRunningInVR() override {
        return unknown_ret();
    }
    unknown_ret BIsRunningOnAlienwareAlpha() override {
        return unknown_ret();
    }
    unknown_ret StartVRDashboard() override {
        return unknown_ret();
    }
    unknown_ret IsVRHeadsetStreamingEnabled(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetVRHeadsetStreamingEnabled(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret GenerateSupportSystemReport() override {
        return unknown_ret();
    }
    unknown_ret GetSupportSystemReport(char *, unsigned int, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppIdForPid(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetClientUIProcess() override {
        return unknown_ret();
    }
    unknown_ret BIsClientUIInForeground() override {
        return unknown_ret();
    }
    unknown_ret SetOverlayChatBrowserInfo(unsigned int, int, int, int, EBrowserType) override {
        return unknown_ret();
    }
    unknown_ret ClearOverlayChatBrowserInfo(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetOverlayChatBrowserInfo(OverlayChatBrowserInfo_t *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret DispatchClientUINotification(EClientUINotificationType, char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RespondToClientUINotification(unsigned int, bool, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret DispatchClientUICommand(char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret DispatchComputerActiveStateChange() override {
        return unknown_ret();
    }
    unknown_ret DispatchOpenURLInClient(char const *, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret UpdateWideVineCDM(char const *) override {
        return unknown_ret();
    }
    unknown_ret DispatchClearAllBrowsingData() override {
        return unknown_ret();
    }
    unknown_ret DispatchClientSettingsChanged() override {
        return unknown_ret();
    }
    unknown_ret DispatchClientPostMessage(char const *, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret IsSteamChinaLauncher() override {
        return unknown_ret();
    }
    unknown_ret InitFilterText(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret FilterText(unsigned int, char *, unsigned int, char const *, bool) override {
        return unknown_ret();
    }
    unknown_ret GetIPv6ConnectivityState(ESteamIPv6ConnectivityProtocol) override {
        return unknown_ret();
    }
    unknown_ret RecordSteamInterfaceCreation(char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret StartRuntimeInformationGathering() override {
        return unknown_ret();
    }
    unknown_ret GetRuntimeInformation() override {
        return unknown_ret();
    }
    unknown_ret GetCloudGamingPlatform() override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientUtilsMap, "SteamUtils");

using IClientUtilsMap = ClientUtilsMap<false>;

AdaptDeclare(ISteamUtils001);
AdaptDefine(ISteamUtils001, IClientUtilsMap, "SteamUtils001") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
};
AdaptDeclare(ISteamUtils002);
AdaptDefine(ISteamUtils002, IClientUtilsMap, "SteamUtils002") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
};
AdaptDeclare(ISteamUtils003);
AdaptDefine(ISteamUtils003, IClientUtilsMap, "SteamUtils003") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
};
AdaptDeclare(ISteamUtils004);
AdaptDefine(ISteamUtils004, IClientUtilsMap, "SteamUtils004") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
    AdaptEmpty(IClientUtilsMap::IsOverlayEnabled),
};
AdaptDeclare(ISteamUtils005);
AdaptDefine(ISteamUtils005, IClientUtilsMap, "SteamUtils005") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
    AdaptEmpty(IClientUtilsMap::IsOverlayEnabled),
    AdaptEmpty(IClientUtilsMap::BOverlayNeedsPresent),
    AdaptPassThrough(IClientUtilsMap::CheckFileSignature),
    AdaptPassThrough(IClientUtilsMap::ShowGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextLength),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextInput),
};
AdaptDeclare(ISteamUtils006);
AdaptDefine(ISteamUtils006, IClientUtilsMap, "SteamUtils006") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
    AdaptEmpty(IClientUtilsMap::IsOverlayEnabled),
    AdaptEmpty(IClientUtilsMap::BOverlayNeedsPresent),
    AdaptPassThrough(IClientUtilsMap::CheckFileSignature),
    AdaptPassThrough(IClientUtilsMap::ShowGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextLength),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetSteamUILanguage),
    AdaptPassThrough(IClientUtilsMap::IsSteamRunningInVR),
};
AdaptDeclare(ISteamUtils007);
AdaptDefine(ISteamUtils007, IClientUtilsMap, "SteamUtils007") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
    AdaptEmpty(IClientUtilsMap::IsOverlayEnabled),
    AdaptEmpty(IClientUtilsMap::BOverlayNeedsPresent),
    AdaptPassThrough(IClientUtilsMap::CheckFileSignature),
    AdaptPassThrough(IClientUtilsMap::ShowGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextLength),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetSteamUILanguage),
    AdaptPassThrough(IClientUtilsMap::IsSteamRunningInVR),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationInset),
    AdaptEmpty(IClientUtilsMap::IsSteamInBigPictureMode),
};
AdaptDeclare(ISteamUtils008);
AdaptDefine(ISteamUtils008, IClientUtilsMap, "SteamUtils008") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
    AdaptEmpty(IClientUtilsMap::IsOverlayEnabled),
    AdaptEmpty(IClientUtilsMap::BOverlayNeedsPresent),
    AdaptPassThrough(IClientUtilsMap::CheckFileSignature),
    AdaptPassThrough(IClientUtilsMap::ShowGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextLength),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetSteamUILanguage),
    AdaptPassThrough(IClientUtilsMap::IsSteamRunningInVR),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationInset),
    AdaptEmpty(IClientUtilsMap::IsSteamInBigPictureMode),
    AdaptPassThrough(IClientUtilsMap::StartVRDashboard),
};
AdaptDeclare(ISteamUtils009);
AdaptDefine(ISteamUtils009, IClientUtilsMap, "SteamUtils009") = {
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceAppActive),
    AdaptPassThrough(IClientUtilsMap::GetSecondsSinceComputerActive),
    AdaptPassThrough(IClientUtilsMap::GetConnectedUniverse),
    AdaptPassThrough(IClientUtilsMap::GetServerRealTime),
    AdaptPassThrough(IClientUtilsMap::GetIPCountry),
    AdaptPassThrough(IClientUtilsMap::GetImageSize),
    AdaptPassThrough(IClientUtilsMap::GetImageRGBA),
    AdaptPassThrough(IClientUtilsMap::GetCSERIPPort),
    AdaptPassThrough(IClientUtilsMap::GetCurrentBatteryPower),
    AdaptPassThrough(IClientUtilsMap::GetAppID),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationPosition),
    AdaptPassThrough(IClientUtilsMap::IsAPICallCompleted),
    AdaptPassThrough(IClientUtilsMap::GetAPICallFailureReason),
    AdaptPassThrough(IClientUtilsMap::GetAPICallResult),
    AdaptEmpty(IClientUtilsMap::RunFrame),
    AdaptEmpty(IClientUtilsMap::GetIPCCallCount),
    AdaptEmpty(IClientUtilsMap::SetWarningMessageHook),
    AdaptEmpty(IClientUtilsMap::IsOverlayEnabled),
    AdaptEmpty(IClientUtilsMap::BOverlayNeedsPresent),
    AdaptPassThrough(IClientUtilsMap::CheckFileSignature),
    AdaptPassThrough(IClientUtilsMap::ShowGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextLength),
    AdaptPassThrough(IClientUtilsMap::GetEnteredGamepadTextInput),
    AdaptPassThrough(IClientUtilsMap::GetSteamUILanguage),
    AdaptPassThrough(IClientUtilsMap::IsSteamRunningInVR),
    AdaptEmpty(IClientUtilsMap::SetOverlayNotificationInset),
    AdaptEmpty(IClientUtilsMap::IsSteamInBigPictureMode),
    AdaptPassThrough(IClientUtilsMap::StartVRDashboard),
    AdaptPassThrough(IClientUtilsMap::IsVRHeadsetStreamingEnabled),
    AdaptPassThrough(IClientUtilsMap::SetVRHeadsetStreamingEnabled),
};
