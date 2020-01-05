#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
//#include "SteamStructs/IClientControllerSerialized.h"

#include "SteamStructs/IClientController.h"
} // namespace Reference

template <bool isServer>
class ClientControllerMap : public Reference::IClientController {
public:
    ClientControllerMap(UserHandle h) {}

    // Inherited via IClientController
    virtual unknown_ret __Destructor1() override {
        return unknown_ret();
    }
#if defined(ARGONX_UNIX)
    virtual unknown_ret __Destructor2() override {
        return unknown_ret();
    }
#endif
    unknown_ret Init(bool, class Reference::IClientControllerSerialized *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret Shutdown() override {
        return unknown_ret();
    }
    unknown_ret RunFrame() override {
        return unknown_ret();
    }
    unknown_ret GetAllControllersStatus(ControllersStatus_t *) override {
        return unknown_ret();
    }
    unknown_ret GetControllerState(unsigned int, SteamControllerStateInternal_t *) override {
        return unknown_ret();
    }
    unknown_ret GetControllerStatusEvent(unsigned int, Voltroller::SteamControllerStatusEvent_t *) override {
        return unknown_ret();
    }
    unknown_ret TriggerHapticPulse(unsigned int, ESteamControllerPad, unsigned short, unsigned short, unsigned short, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsControllerConnected(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetConnectedControllers(unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret GetConnectedControllers(unsigned int, unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret GetDigitalActionData(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetAnalogActionData(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret ActivateActionSet(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetCurrentActionSet(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret ActivateActionSetLayer(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret DeactivateActionSetLayer(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret DeactivateAllActionSetLayers(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetActiveActionSetLayers(unsigned int, unsigned long long, unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret ShowBindingPanel(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetControllerTypeForHandle(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetGamepadIndexForHandle(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetHandleForGamepadIndex(int) override {
        return unknown_ret();
    }
    unknown_ret GetDigitalActionHandle(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetAnalogActionHandle(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetDigitalActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    unknown_ret GetDigitalActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *) override {
        return unknown_ret();
    }
    unknown_ret GetAnalogActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    unknown_ret GetAnalogActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *) override {
        return unknown_ret();
    }
    unknown_ret GetDigitalActionOrigins_Legacy(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    unknown_ret GetAnalogActionOrigins_Legacy(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    unknown_ret TriggerHapticPulseOnHandle(unsigned long long, ESteamControllerPad, unsigned short) override {
        return unknown_ret();
    }
    unknown_ret TriggerRepeatedHapticPulseOnHandle(unsigned long long, ESteamControllerPad, unsigned short, unsigned short, unsigned short, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret TriggerVibrationOnHandle(unsigned long long, unsigned short, unsigned short) override {
        return unknown_ret();
    }
    unknown_ret SetLEDColorOnHandle(unsigned long long, unsigned char, unsigned char, unsigned char, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret HasGameMapping(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret FindControllerByAPIHandle(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetGlyphForActionOrigin(EControllerActionOrigin) override {
        return unknown_ret();
    }
    unknown_ret GetGlyphForXboxOrigin(EXboxOrigin) override {
        return unknown_ret();
    }
    unknown_ret GetStringForActionOrigin(EControllerActionOrigin) override {
        return unknown_ret();
    }
    unknown_ret GetStringForXboxOrigin(EXboxOrigin) override {
        return unknown_ret();
    }
    unknown_ret GetActionOriginFromXboxOrigin(unsigned long long, EXboxOrigin) override {
        return unknown_ret();
    }
    unknown_ret TranslateActionOrigin(ESteamInputType, EControllerActionOrigin) override {
        return unknown_ret();
    }
    unknown_ret GetInputTypeForHandle(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret TranslateSteamInputOriginToSteamControllerOrigin(EInputActionOrigin) override {
        return unknown_ret();
    }
    unknown_ret TranslateSteamControllerOriginToSteamInputOrigin(EControllerActionOrigin) override {
        return unknown_ret();
    }
    unknown_ret GetMotionData(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetMotionDataDisabled(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetCurrentFocusedAppID(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetStickExtents(unsigned int, int, short *, short *, short *, short *) override {
        return unknown_ret();
    }
    unknown_ret GetControllerBindingRevision(unsigned int, unsigned long long, int *, int *) override {
        return unknown_ret();
    }
    unknown_ret GetRemotePlaySessionID(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret CursorVisibilityChanged(bool) override {
        return unknown_ret();
    }
    unknown_ret Validate(CValidator &, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetNumConnectedControllers() override {
        return unknown_ret();
    }
    unknown_ret GetControllerDetails(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret FactoryReset(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetDefaultConfig(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CalibrateTrackpads(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CalibrateJoystick(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CalibrateIMU(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetAudioMapping(unsigned int, CUtlVector<signed char, CUtlMemory<signed char>> *) override {
        return unknown_ret();
    }
    unknown_ret PlayAudio(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetUserLedColor(unsigned int, unsigned char, unsigned char, unsigned char) override {
        return unknown_ret();
    }
    unknown_ret SetStickExtents(unsigned int, int, short, short, short, short) override {
        return unknown_ret();
    }
    unknown_ret ResetStickExtents(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetRumble(unsigned int, int, int, unsigned short, unsigned short) override {
        return unknown_ret();
    }
    unknown_ret SendIRCode(unsigned int, int, bool, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret StopIRCode(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret InvalidateBindingCache() override {
        return unknown_ret();
    }
    unknown_ret InvalidateBindingCacheForApp(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret LoadConfigFromVDFString(unsigned int, char const *, unsigned int, SteamControllerAppSettings_t) override {
        return unknown_ret();
    }
    unknown_ret ActivateConfig(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret WarmOptInStatus(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BIsStreamingController(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetControllerEnableSupport(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BAllowAppConfigForController(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ResetControllerEnableCache() override {
        return unknown_ret();
    }
    unknown_ret BShouldShowThirdPartyRemapperWarning(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetInputGenerated(bool, int) override {
        return unknown_ret();
    }
    unknown_ret BInputGenerated() override {
        return unknown_ret();
    }
    unknown_ret GetCurrentActionSetHandleForRunningApp(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CreateBindingInstanceFromVDFString(CControllerMappingCreateData const *) override {
        return unknown_ret();
    }
    unknown_ret FreeBindingInstance(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ConvertBindingToNewControllerType(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret IsModified(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ClearModified(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetBindingVDFString(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalizationTokenCount(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetLocalizationToken(unsigned int, int, CUtlString *) override {
        return unknown_ret();
    }
    unknown_ret GetLocalizedString(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetSourceGroupBindingCount(unsigned int, EControllerSource) override {
        return unknown_ret();
    }
    unknown_ret GetSourceGroupBindingInfo(unsigned int, EControllerSource, int, SetId, SourceGroupBindingInfo_t *) override {
        return unknown_ret();
    }
    unknown_ret SetSourceGroupBindingActive(unsigned int, EControllerSource, GroupId, bool, SetId, GameActionGid) override {
        return unknown_ret();
    }
    unknown_ret CreateSourceGroupBinding(unsigned int, EControllerSource, EControllerSourceMode, bool, PresetId) override {
        return unknown_ret();
    }
    unknown_ret BAreLayerAndParentModesEquivalent(unsigned int, LayerAGroupId, GroupId) override {
        return unknown_ret();
    }
    unknown_ret GetGroupSetting(unsigned int, GroupId, EControllerSetting, int *) override {
        return unknown_ret();
    }
    unknown_ret SetGroupSetting(unsigned int, GroupId, EControllerSetting, int) override {
        return unknown_ret();
    }
    unknown_ret GetGroupSettingDefault(unsigned int, GroupId, EControllerSetting, int *) override {
        return unknown_ret();
    }
    unknown_ret SetGroupBinding(unsigned int, GroupId, EControllerModeInput, ActivatorId, BindingAction_t *, char const *, IconBindingData_t *) override {
        return unknown_ret();
    }
    unknown_ret GetGroupBinding(unsigned int, GroupId, EControllerModeInput, ActivatorId, CUtlVector<BindingAction_t, CUtlMemory<BindingAction_t>> *, CUtlString *, IconBindingData_t *) override {
        return unknown_ret();
    }
    unknown_ret RemoveGroupBinding(unsigned int, GroupId, EControllerModeInput, ActivatorId) override {
        return unknown_ret();
    }
    unknown_ret GetActivatorSetting(unsigned int, GroupId, EControllerModeInput, ActivatorId, EControllerSetting, int *) override {
        return unknown_ret();
    }
    unknown_ret SetActivatorSetting(unsigned int, GroupId, EControllerModeInput, ActivatorId, EControllerSetting, int) override {
        return unknown_ret();
    }
    unknown_ret GetActivatorSettingDefault(unsigned int, GroupId, EControllerModeInput, ActivatorId, EControllerSetting, int *) override {
        return unknown_ret();
    }
    unknown_ret GetParentGroupForLayerGroup(unsigned int, GroupId) override {
        return unknown_ret();
    }
    unknown_ret GetParentPresetForLayerPreset(unsigned int, LayerAPresetId) override {
        return unknown_ret();
    }
    unknown_ret GetGroupActivatorsForInput(unsigned int, GroupId, EControllerModeInput, CUtlVector<ActivatorInfo_t, CUtlMemory<ActivatorInfo_t>> *) override {
        return unknown_ret();
    }
    unknown_ret ReplaceActivator(unsigned int, GroupId, EControllerModeInput, ActivatorId, EControllerActivationType) override {
        return unknown_ret();
    }
    unknown_ret AddActivator(unsigned int, GroupId, EControllerModeInput) override {
        return unknown_ret();
    }
    unknown_ret RemoveActivator(unsigned int, GroupId, EControllerModeInput, ActivatorId) override {
        return unknown_ret();
    }
    unknown_ret CopyActivator(unsigned int, GroupId, GroupId, EControllerModeInput, ActivatorId) override {
        return unknown_ret();
    }
    unknown_ret IsActivatorSettingsDefault(unsigned int, GroupId, EControllerModeInput, ActivatorId) override {
        return unknown_ret();
    }
    unknown_ret SetModeShiftBinding(unsigned int, Voltroller::DigitalIO, PresetId, BindingAction_t *, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetModeShiftBinding(unsigned int, Voltroller::DigitalIO, EControllerSource, PresetId, BindingAction_t *, CUtlString *) override {
        return unknown_ret();
    }
    unknown_ret GetGameActionSets(unsigned int, CUtlVector<CGameActionSet *, CUtlMemory<CGameActionSet *>> *) override {
        return unknown_ret();
    }
    unknown_ret GetBaseGameActionSets(unsigned int, CUtlVector<CBaseGameActionSet *, CUtlMemory<CBaseGameActionSet *>> *) override {
        return unknown_ret();
    }
    unknown_ret GetLayerGameActionSets(unsigned int, CUtlVector<CLayerGameActionSet *, CUtlMemory<CLayerGameActionSet *>> *) override {
        return unknown_ret();
    }
    unknown_ret GetGameActionSetById(unsigned int, ASetId) override {
        return unknown_ret();
    }
    unknown_ret AddActionSet(unsigned int, CGameActionSet *) override {
        return unknown_ret();
    }
    unknown_ret DeleteActionSet(unsigned int, CGameActionSet *) override {
        return unknown_ret();
    }
    unknown_ret RenameActionSet(unsigned int, CGameActionSet *) override {
        return unknown_ret();
    }
    unknown_ret GetBindingSetting(unsigned int, EControllerSetting, int *) override {
        return unknown_ret();
    }
    unknown_ret SetBindingSetting(unsigned int, EControllerSetting, int) override {
        return unknown_ret();
    }
    unknown_ret GetBindingTitle(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetBindingTitle(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetBindingDescription(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetBindingRevision(unsigned int, int *, int *) override {
        return unknown_ret();
    }
    unknown_ret BBindingMajorRevisionMismatch(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetBindingDescription(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetBindingControllerType(unsigned int, EControllerType) override {
        return unknown_ret();
    }
    unknown_ret GetBindingControllerType(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetBindingCreator(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetBindingCreator(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetConfigFeatures(unsigned int, CUtlVector<EControllerConfigFeature, CUtlMemory<EControllerConfigFeature>> *) override {
        return unknown_ret();
    }
    unknown_ret GetAllBindings(unsigned int, CUtlVector<BindingAction_t, CUtlMemory<BindingAction_t>> *, CUtlVector<CUtlString, CUtlMemory<CUtlString>> *) override {
        return unknown_ret();
    }
    unknown_ret TriggerVibration(unsigned int, unsigned short, unsigned short) override {
        return unknown_ret();
    }
    unknown_ret SetLEDColor(unsigned int, unsigned char, unsigned char, unsigned char, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetDonglePairingMode(bool, int) override {
        return unknown_ret();
    }
    unknown_ret SetControllerPairingConnectionState(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetControllerKeyboardMouseState(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetLocalControllerConnectionState(unsigned int, EControllerConnectionState) override {
        return unknown_ret();
    }
    unknown_ret ReserveSteamController() override {
        return unknown_ret();
    }
    unknown_ret CancelSteamControllerReservations() override {
        return unknown_ret();
    }
    unknown_ret OpenStreamingSession(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CloseStreamingSession(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret InitiateBootloaderFirmwareUpdate(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret InitiateISPFirmwareUpdate(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret FlashControllerFirmware(unsigned int, CUtlBuffer *, unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret TurnOffController(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetGyroOn(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret SetControllerSetting(unsigned int, Voltroller::ControllerSetting *) override {
        return unknown_ret();
    }
    unknown_ret EnumerateControllers() override {
        return unknown_ret();
    }
    unknown_ret StartConfigSets(unsigned int, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret AddConfigSet(char const *, unsigned long long, char const *) override {
        return unknown_ret();
    }
    unknown_ret FinishConfigSets(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BControllerHasUniqueConfigForAppID(unsigned int, CUtlString *) override {
        return unknown_ret();
    }
    unknown_ret DeRegisterController(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetPersonalizationFile(unsigned int, unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetPersonalizationFileID(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret LoadControllerPersonalizationFile(unsigned int, char const *, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret SaveControllerPersonalizationFile(unsigned int, unsigned int, ControllerIdentity_t *) override {
        return unknown_ret();
    }
    unknown_ret BGetTouchConfigData(unsigned int, unsigned int, unsigned int *, CUtlBuffer *, CUtlBuffer *) override {
        return unknown_ret();
    }
    unknown_ret BSaveTouchConfigLayout(unsigned int, unsigned int, CUtlBuffer const *) override {
        return unknown_ret();
    }
    unknown_ret BAnyControllerOptedInAndAvailible(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetTouchKeysForPopupMenu(unsigned int, unsigned int, PopupMenuTouchKey_t *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret PopupMenuTouchKeyClicked(unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CheckMappingForEvents() override {
        return unknown_ret();
    }
    unknown_ret AccessControllerInputGeneratorMouseButton(unsigned int, Voltroller::MouseButtons, bool) override {
        return unknown_ret();
    }
    unknown_ret GetEmulatedOutputState() override {
        return unknown_ret();
    }
    unknown_ret DeactivateActionSetLayer(unsigned int, unsigned long long, LayerASetId) override {
        return unknown_ret();
    }
    unknown_ret GetActionSetHandle(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetActionSetHandleByTitle(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret StopAnalogActionMomentum(unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret StartTrackingCallback(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetControllerUsageData(unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientControllerMap, "SteamController");

using IClientControllerMap = ClientControllerMap<false>;

AdaptDeclare(ISteamController001);
AdaptDefine(ISteamController001, IClientControllerMap, "SteamController002") = {
    AdaptPassThrough(IClientControllerMap::Init),
    AdaptPassThrough(IClientControllerMap::Shutdown),
    AdaptPassThrough(IClientControllerMap::RunFrame),
    AdaptPassThrough(IClientControllerMap::GetControllerState),
    AdaptPassThrough(IClientControllerMap::TriggerHapticPulse),
    AdaptEmpty(IClientControllerMap::SetOverrideMode),
};
AdaptDeclare(ISteamController003);
AdaptDefine(ISteamController003, IClientControllerMap, "SteamController003") = {
    AdaptPassThrough(IClientControllerMap::Init),
    AdaptPassThrough(IClientControllerMap::Shutdown),
    AdaptPassThrough(IClientControllerMap::RunFrame),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned long long *), IClientControllerMap::GetConnectedControllers),
    AdaptPassThrough(IClientControllerMap::ShowBindingPanel),
    AdaptPassThrough(IClientControllerMap::GetActionSetHandle),
    AdaptPassThrough(IClientControllerMap::ActivateActionSet),
    AdaptPassThrough(IClientControllerMap::GetCurrentActionSet),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionHandle),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetDigitalActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionHandle),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::StopAnalogActionMomentum),
    AdaptPassThrough(IClientControllerMap::TriggerHapticPulse),
    AdaptPassThrough(IClientControllerMap::TriggerRepeatedHapticPulseOnHandle),
};
AdaptDeclare(ISteamController004);
AdaptDefine(ISteamController004, IClientControllerMap, "SteamController004") = {
    AdaptPassThrough(IClientControllerMap::Init),
    AdaptPassThrough(IClientControllerMap::Shutdown),
    AdaptPassThrough(IClientControllerMap::RunFrame),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned long long *), IClientControllerMap::GetConnectedControllers),
    AdaptPassThrough(IClientControllerMap::ShowBindingPanel),
    AdaptPassThrough(IClientControllerMap::GetActionSetHandle),
    AdaptPassThrough(IClientControllerMap::ActivateActionSet),
    AdaptPassThrough(IClientControllerMap::GetCurrentActionSet),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionHandle),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetDigitalActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionHandle),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::StopAnalogActionMomentum),
    AdaptPassThrough(IClientControllerMap::TriggerHapticPulse),
    AdaptPassThrough(IClientControllerMap::TriggerRepeatedHapticPulseOnHandle),
    AdaptPassThrough(IClientControllerMap::GetGamepadIndexForHandle),
    AdaptPassThrough(IClientControllerMap::GetHandleForGamepadIndex),
    AdaptPassThrough(IClientControllerMap::GetMotionData),
    AdaptEmpty(IClientControllerMap::ShowDigitalActionOrigins),
    AdaptEmpty(IClientControllerMap::ShowAnalogActionOrigins),
};
AdaptDeclare(ISteamController005);
AdaptDefine(ISteamController005, IClientControllerMap, "SteamController005") = {
    AdaptPassThrough(IClientControllerMap::Init),
    AdaptPassThrough(IClientControllerMap::Shutdown),
    AdaptPassThrough(IClientControllerMap::RunFrame),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned long long *), IClientControllerMap::GetConnectedControllers),
    AdaptPassThrough(IClientControllerMap::ShowBindingPanel),
    AdaptPassThrough(IClientControllerMap::GetActionSetHandle),
    AdaptPassThrough(IClientControllerMap::ActivateActionSet),
    AdaptPassThrough(IClientControllerMap::GetCurrentActionSet),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionHandle),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetDigitalActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionHandle),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::StopAnalogActionMomentum),
    AdaptPassThrough(IClientControllerMap::TriggerHapticPulse),
    AdaptPassThrough(IClientControllerMap::TriggerRepeatedHapticPulseOnHandle),
    AdaptPassThrough(IClientControllerMap::TriggerVibration),
    AdaptPassThrough(IClientControllerMap::SetLEDColor),
    AdaptPassThrough(IClientControllerMap::GetGamepadIndexForHandle),
    AdaptPassThrough(IClientControllerMap::GetHandleForGamepadIndex),
    AdaptPassThrough(IClientControllerMap::GetMotionData),
    AdaptEmpty(IClientControllerMap::ShowDigitalActionOrigins),
    AdaptEmpty(IClientControllerMap::ShowAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetStringForActionOrigin),
    AdaptPassThrough(IClientControllerMap::GetGlyphForActionOrigin),
};
AdaptDeclare(ISteamController006);
AdaptDefine(ISteamController006, IClientControllerMap, "SteamController006") = {
    AdaptPassThrough(IClientControllerMap::Init),
    AdaptPassThrough(IClientControllerMap::Shutdown),
    AdaptPassThrough(IClientControllerMap::RunFrame),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned long long *), IClientControllerMap::GetConnectedControllers),
    AdaptPassThrough(IClientControllerMap::ShowBindingPanel),
    AdaptPassThrough(IClientControllerMap::GetActionSetHandle),
    AdaptPassThrough(IClientControllerMap::ActivateActionSet),
    AdaptPassThrough(IClientControllerMap::GetCurrentActionSet),
    AdaptPassThrough(IClientControllerMap::ActivateActionSetLayer),
    AdaptEmpty(IClientControllerMap::DeactivateActionSetLayer),
    AdaptPassThrough(IClientControllerMap::DeactivateAllActionSetLayers),
    AdaptPassThrough(IClientControllerMap::GetActiveActionSetLayers),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionHandle),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetDigitalActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionHandle),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::StopAnalogActionMomentum),
    AdaptPassThrough(IClientControllerMap::TriggerHapticPulse),
    AdaptPassThrough(IClientControllerMap::TriggerRepeatedHapticPulseOnHandle),
    AdaptPassThrough(IClientControllerMap::TriggerVibration),
    AdaptPassThrough(IClientControllerMap::SetLEDColor),
    AdaptPassThrough(IClientControllerMap::GetGamepadIndexForHandle),
    AdaptPassThrough(IClientControllerMap::GetHandleForGamepadIndex),
    AdaptPassThrough(IClientControllerMap::GetMotionData),
    AdaptEmpty(IClientControllerMap::ShowDigitalActionOrigins),
    AdaptEmpty(IClientControllerMap::ShowAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetStringForActionOrigin),
    AdaptPassThrough(IClientControllerMap::GetGlyphForActionOrigin),
    AdaptPassThrough(IClientControllerMap::GetInputTypeForHandle),
};
AdaptDeclare(ISteamController007);
AdaptDefine(ISteamController007, IClientControllerMap, "SteamController007") = {
    AdaptPassThrough(IClientControllerMap::Init),
    AdaptPassThrough(IClientControllerMap::Shutdown),
    AdaptPassThrough(IClientControllerMap::RunFrame),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned long long *), IClientControllerMap::GetConnectedControllers),
    AdaptPassThrough(IClientControllerMap::GetActionSetHandle),
    AdaptPassThrough(IClientControllerMap::ActivateActionSet),
    AdaptPassThrough(IClientControllerMap::GetCurrentActionSet),
    AdaptPassThrough(IClientControllerMap::ActivateActionSetLayer),
    AdaptEmpty(IClientControllerMap::DeactivateActionSetLayer),
    AdaptPassThrough(IClientControllerMap::DeactivateAllActionSetLayers),
    AdaptPassThrough(IClientControllerMap::GetActiveActionSetLayers),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionHandle),
    AdaptPassThrough(IClientControllerMap::GetDigitalActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetDigitalActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionHandle),
    AdaptPassThrough(IClientControllerMap::GetAnalogActionData),
    AdaptOverload(unknown_ret (IClientControllerMap::*)(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *), IClientControllerMap::GetAnalogActionOrigins),
    AdaptPassThrough(IClientControllerMap::GetGlyphForActionOrigin),
    AdaptPassThrough(IClientControllerMap::GetStringForActionOrigin),
    AdaptPassThrough(IClientControllerMap::StopAnalogActionMomentum),
    AdaptPassThrough(IClientControllerMap::GetMotionData),
    AdaptPassThrough(IClientControllerMap::TriggerHapticPulse),
    AdaptPassThrough(IClientControllerMap::TriggerRepeatedHapticPulseOnHandle),
    AdaptPassThrough(IClientControllerMap::TriggerVibration),
    AdaptPassThrough(IClientControllerMap::SetLEDColor),
    AdaptPassThrough(IClientControllerMap::ShowBindingPanel),
    AdaptPassThrough(IClientControllerMap::GetInputTypeForHandle),
    AdaptPassThrough(IClientControllerMap::GetGamepadIndexForHandle),
    AdaptPassThrough(IClientControllerMap::GetHandleForGamepadIndex),
    AdaptPassThrough(IClientControllerMap::GetStringForXboxOrigin),
    AdaptPassThrough(IClientControllerMap::GetGlyphForXboxOrigin),
    AdaptPassThrough(IClientControllerMap::GetActionOriginFromXboxOrigin),
    AdaptPassThrough(IClientControllerMap::TranslateActionOrigin),
};
