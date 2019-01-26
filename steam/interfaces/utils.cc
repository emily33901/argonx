#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientUtils.h"
}

extern Pipe *clientPipe;

class IClientUtilsMap : public Reference::IClientUtils {
public:
    // Inherited via IClientUtils
    virtual unknown_ret GetInstallPath() override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserBaseFolderInstallImage() override {
        return unknown_ret();
    }
    virtual unknown_ret GetManagedContentRoot() override {
        return unknown_ret();
    }
    virtual unknown_ret GetSecondsSinceAppActive() override {
        Rpc<decltype(&IClientUtilsMap::GetSecondsSinceAppActive)> r{this, &IClientUtilsMap::GetSecondsSinceAppActive, InterfaceTarget::utils};
        return r.Call(0, *clientPipe);
    }
    virtual unknown_ret GetSecondsSinceComputerActive() override {
        return unknown_ret();
    }
    virtual unknown_ret SetComputerActive() override {
        return unknown_ret();
    }
    virtual unknown_ret GetConnectedUniverse() override {
        return unknown_ret();
    }
    virtual unknown_ret GetServerRealTime() override {
        return unknown_ret();
    }
    virtual unknown_ret GetIPCountry() override {
        return unknown_ret();
    }
    virtual unknown_ret GetImageSize(int, unsigned int *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetImageRGBA(int, unsigned char *, int) override {
        return unknown_ret();
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
    virtual unknown_ret SetOfflineMode(bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetOfflineMode() override {
        return unknown_ret();
    }
    virtual unknown_ret SetAppIDForCurrentPipe(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppID() override {
        return unknown_ret();
    }
    virtual unknown_ret SetAPIDebuggingActive(bool a, bool b) override {
        Rpc<decltype(&IClientUtilsMap::SetAPIDebuggingActive)> r{this, &IClientUtilsMap::SetAPIDebuggingActive, InterfaceTarget::utils};
        r.SetArgs(a, b);
        return r.Call(0, *clientPipe);
    }
    virtual unknown_ret AllocPendingAPICallHandle() override {
        return unknown_ret();
    }
    virtual unknown_ret IsAPICallCompleted(unsigned long long a, bool *b) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAPICallFailureReason(unsigned long long a) override {
        Rpc<decltype(&IClientUtilsMap::GetAPICallFailureReason)> r{this, &IClientUtilsMap::GetAPICallFailureReason, InterfaceTarget::utils};
        r.SetArgs(a);
        return r.Call(0, *clientPipe);
    }
    virtual unknown_ret GetAPICallResult(unsigned long long, void *, int, int, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAPICallResultWithoutPostingCallback(unsigned long long, void const *, int, int) override {
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
    virtual unknown_ret CheckFileSignature(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBuildID() override {
        return unknown_ret();
    }
    virtual unknown_ret SetCurrentUIMode(EUIMode) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentUIMode() override {
        return unknown_ret();
    }
    virtual unknown_ret ShutdownLauncher(bool, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLauncherType(ELauncherType) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLauncherType() override {
        return unknown_ret();
    }
    virtual unknown_ret ShowGamepadTextInput(EGamepadTextInputMode, EGamepadTextInputLineMode, char const *, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetEnteredGamepadTextLength() override {
        return unknown_ret();
    }
    virtual unknown_ret GetEnteredGamepadTextInput(char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GamepadTextInputClosed(int, bool, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSpew(int, int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret BDownloadsDisabled() override {
        return unknown_ret();
    }
    virtual unknown_ret SetFocusedWindow(CGameID, unsigned long long, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSteamUILanguage() override {
        return unknown_ret();
    }
    virtual unknown_ret CheckSteamReachable() override {
        return unknown_ret();
    }
    virtual unknown_ret SetLastGameLaunchMethod(EGameLaunchMethod) override {
        return unknown_ret();
    }
    virtual unknown_ret SetVideoAdapterInfo(int, int, int, int, int, int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetControllerOverrideMode(CGameID, char const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayWindowFocusForPipe(bool, bool, CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGameOverlayUIInstanceFocusGameID(bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetControllerConfigFileForAppID(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerConfigFileForAppID(unsigned int, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsSteamRunningInVR() override {
        return unknown_ret();
    }
    virtual unknown_ret BIsRunningOnAlienwareAlpha() override {
        return unknown_ret();
    }
    virtual unknown_ret StartVRDashboard() override {
        return unknown_ret();
    }
    virtual unknown_ret IsVRHeadsetStreamingEnabled(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetVRHeadsetStreamingEnabled(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GenerateSupportSystemReport() override {
        return unknown_ret();
    }
    virtual unknown_ret GetSupportSystemReport(char *, unsigned int, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAppIdForPid(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetClientUIProcess() override {
        return unknown_ret();
    }
    virtual unknown_ret BIsClientUIInForeground() override {
        return unknown_ret();
    }
    virtual unknown_ret SetOverlayChatBrowserInfo(unsigned int, int, int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearOverlayChatBrowserInfo(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetOverlayChatBrowserInfo(OverlayChatBrowserInfo_t *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret DispatchClientUINotification(EClientUINotificationType, char const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RespondToClientUINotification(unsigned int, bool, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret DispatchClientUICommand(char const *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret DispatchComputerActiveStateChange() override {
        return unknown_ret();
    }
    virtual unknown_ret DispatchOpenURLInClient(char const *, unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdateWideVineCDM(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret DispatchClearAllBrowsingData() override {
        return unknown_ret();
    }
};

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
