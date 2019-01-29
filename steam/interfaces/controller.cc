#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientControllerSerialized.h"

#include "SteamStructs/IClientController.h"
} // namespace Reference

template<bool isServer>
class ClientControllerMap : public Reference::IClientController {
public:
    // Inherited via IClientController
    virtual unknown_ret __Destructor1() override {
        return unknown_ret();
    }
#if defined(ARGONX_UNIX)
    virtual unknown_ret __Destructor2() override {
        return unknown_ret();
    }
#endif
    virtual unknown_ret Init(bool, Reference::IClientControllerSerialized *) override {
        return unknown_ret();
    }
    virtual unknown_ret Shutdown() override {
        return unknown_ret();
    }
    virtual unknown_ret RunFrame() override {
        return unknown_ret();
    }
    virtual unknown_ret GetAllControllersStatus(ControllersStatus_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerState(unsigned int, SteamControllerStateInternal_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerStatusEvent(unsigned int, Voltroller::SteamControllerStatusEvent_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret TriggerHapticPulse(unsigned int, ESteamControllerPad, unsigned short, unsigned short, unsigned short, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsControllerConnected(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConnectedControllers(unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConnectedControllers(unsigned int, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDigitalActionData(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAnalogActionData(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateActionSet(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentActionSet(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateActionSetLayer(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret DeactivateActionSetLayer(unsigned int, unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret DeactivateAllActionSetLayers(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetActiveActionSetLayers(unsigned int, unsigned long long, unsigned long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret ShowBindingPanel(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerTypeForHandle(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGamepadIndexForHandle(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetHandleForGamepadIndex(int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDigitalActionHandle(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAnalogActionHandle(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDigitalActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDigitalActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAnalogActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAnalogActionOrigins(unsigned int, unsigned long long, unsigned long long, unsigned long long, EInputActionOrigin *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDigitalActionOrigins_Legacy(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAnalogActionOrigins_Legacy(unsigned int, unsigned long long, unsigned long long, unsigned long long, EControllerActionOrigin *) override {
        return unknown_ret();
    }
    virtual unknown_ret TriggerHapticPulseOnHandle(unsigned long long, ESteamControllerPad, unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret TriggerRepeatedHapticPulseOnHandle(unsigned long long, ESteamControllerPad, unsigned short, unsigned short, unsigned short, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret TriggerVibrationOnHandle(unsigned long long, unsigned short, unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLEDColorOnHandle(unsigned long long, unsigned char, unsigned char, unsigned char, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret HasGameMapping(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret FindControllerByAPIHandle(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGlyphForActionOrigin(EControllerActionOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGlyphForXboxOrigin(EXboxOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStringForActionOrigin(EControllerActionOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStringForXboxOrigin(EXboxOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret GetActionOriginFromXboxOrigin(unsigned long long, EXboxOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret TranslateActionOrigin(ESteamInputType, EControllerActionOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret GetInputTypeForHandle(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret TranslateSteamInputOriginToSteamControllerOrigin(EInputActionOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret TranslateSteamControllerOriginToSteamInputOrigin(EControllerActionOrigin) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMotionData(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMotionDataDisabled(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentFocusedAppID(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret Validate(CValidator &, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumConnectedControllers() override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerDetails(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret FactoryReset(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDefaultConfig(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CalibrateTrackpads(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CalibrateJoystick(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CalibrateIMU(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAudioMapping(unsigned int, CUtlVector<signed char, CUtlMemory<signed char>> *) override {
        return unknown_ret();
    }
    virtual unknown_ret PlayAudio(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetUserLedColor(unsigned int, unsigned char, unsigned char, unsigned char) override {
        return unknown_ret();
    }
    virtual unknown_ret SetRumble(unsigned int, int, int, unsigned short, unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret SendIRCode(unsigned int, int, bool, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret StopIRCode(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret InvalidateBindingCache() override {
        return unknown_ret();
    }
    virtual unknown_ret LoadConfigFromVDFString(unsigned int, char const *, unsigned int, SteamControllerAppSettings_t) override {
        return unknown_ret();
    }
    virtual unknown_ret ActivateConfig(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret WarmOptInStatus(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BIsStreamingController(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerEnableSupport(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BAllowAppConfigForController(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ResetControllerEnableCache() override {
        return unknown_ret();
    }
    virtual unknown_ret BShouldShowThirdPartyRemapperWarning(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetInputGenerated(bool, int) override {
        return unknown_ret();
    }
    virtual unknown_ret BInputGenerated() override {
        return unknown_ret();
    }
    virtual unknown_ret GetCurrentActionSetHandleForRunningApp(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateBindingInstanceFromVDFString(CControllerMappingCreateData const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FreeBindingInstance(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ConvertBindingToNewControllerType(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsModified(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearModified(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBindingVDFString(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLocalizationTokenCount(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLocalizationToken(unsigned int, int, CUtlString *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLocalizedString(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSourceGroupBindingCount(unsigned int, EControllerSource) override {
        return unknown_ret();
    }
    virtual unknown_ret GetSourceGroupBindingInfo(unsigned int, EControllerSource, int, int, SourceGroupBindingInfo_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetSourceGroupBindingActive(unsigned int, EControllerSource, int, bool, int, int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret CreateSourceGroupBinding(unsigned int, EControllerSource, EControllerSourceMode, bool, int) override {
        return unknown_ret();
    }
    virtual unknown_ret BAreLayerAndParentModesEquivalent(unsigned int, int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGroupSetting(unsigned int, int, EControllerSetting, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetGroupSetting(unsigned int, int, EControllerSetting, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGroupSettingDefault(unsigned int, int, EControllerSetting, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetGroupBinding(unsigned int, int, EControllerModeInput, int, BindingAction_t *, char const *, IconBindingData_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGroupBinding(unsigned int, int, EControllerModeInput, int, CUtlVector<BindingAction_t, CUtlMemory<BindingAction_t>> *, CUtlString *, IconBindingData_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveGroupBinding(unsigned int, int, EControllerModeInput, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetActivatorSetting(unsigned int, int, EControllerModeInput, int, EControllerSetting, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetActivatorSetting(unsigned int, int, EControllerModeInput, int, EControllerSetting, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetActivatorSettingDefault(unsigned int, int, EControllerModeInput, int, EControllerSetting, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetParentGroupForLayerGroup(unsigned int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetParentPresetForLayerPreset(unsigned int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGroupActivatorsForInput(unsigned int, int, EControllerModeInput, CUtlVector<ActivatorInfo_t, CUtlMemory<ActivatorInfo_t>> *) override {
        return unknown_ret();
    }
    virtual unknown_ret ReplaceActivator(unsigned int, int, EControllerModeInput, int, EControllerActivationType) override {
        return unknown_ret();
    }
    virtual unknown_ret AddActivator(unsigned int, int, EControllerModeInput) override {
        return unknown_ret();
    }
    virtual unknown_ret RemoveActivator(unsigned int, int, EControllerModeInput, int) override {
        return unknown_ret();
    }
    virtual unknown_ret CopyActivator(unsigned int, int, int, EControllerModeInput, int) override {
        return unknown_ret();
    }
    virtual unknown_ret IsActivatorSettingsDefault(unsigned int, int, EControllerModeInput, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetModeShiftBinding(unsigned int, Voltroller::DigitalIO, int, BindingAction_t *, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetModeShiftBinding(unsigned int, Voltroller::DigitalIO, EControllerSource, int, BindingAction_t *, CUtlString *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGameActionSets(unsigned int, CUtlVector<CGameActionSet *, CUtlMemory<CGameActionSet *>> *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGameActionSetByID(unsigned int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret AddActionSet(unsigned int, CGameActionSet *) override {
        return unknown_ret();
    }
    virtual unknown_ret DeleteActionSet(unsigned int, CGameActionSet *) override {
        return unknown_ret();
    }
    virtual unknown_ret RenameActionSet(unsigned int, CGameActionSet *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBindingSetting(unsigned int, EControllerSetting, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetBindingSetting(unsigned int, EControllerSetting, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBindingTitle(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetBindingTitle(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBindingDescription(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetBindingDescription(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetBindingControllerType(unsigned int, EControllerType) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBindingControllerType(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetBindingCreator(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetBindingCreator(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetConfigFeatures(unsigned int, CUtlVector<EControllerConfigFeature, CUtlMemory<EControllerConfigFeature>> *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAllBindings(unsigned int, CUtlVector<BindingAction_t, CUtlMemory<BindingAction_t>> *, CUtlVector<CUtlString, CUtlMemory<CUtlString>> *) override {
        return unknown_ret();
    }
    virtual unknown_ret TriggerVibration(unsigned int, unsigned short, unsigned short) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLEDColor(unsigned int, unsigned char, unsigned char, unsigned char, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetDonglePairingMode(bool, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetControllerPairingConnectionState(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetControllerKeyboardMouseState(unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SetLocalControllerConnectionState(unsigned int, EControllerConnectionState) override {
        return unknown_ret();
    }
    virtual unknown_ret ReserveSteamController() override {
        return unknown_ret();
    }
    virtual unknown_ret CancelSteamControllerReservations() override {
        return unknown_ret();
    }
    virtual unknown_ret OpenStreamingSession(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CloseStreamingSession(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret InitiateBootloaderFirmwareUpdate(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret InitiateISPFirmwareUpdate(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret FlashControllerFirmware(unsigned int, CUtlBuffer *, unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret TurnOffController(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetGyroOn(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret SetControllerSetting(unsigned int, Voltroller::ControllerSetting *) override {
        return unknown_ret();
    }
    virtual unknown_ret EnumerateControllers() override {
        return unknown_ret();
    }
    virtual unknown_ret StartConfigSets(unsigned int, unsigned int, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret AddConfigSet(char const *, unsigned long long, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret FinishConfigSets(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret BControllerHasUniqueConfigForAppID(unsigned int, CUtlString *) override {
        return unknown_ret();
    }
    virtual unknown_ret DeRegisterController(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetPersonalizationFile(unsigned int, unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetPersonalizationFileID(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret LoadControllerPersonalizationFile(unsigned int, char const *, bool, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret SaveControllerPersonalizationFile(unsigned int, unsigned int, ControllerIdentity_t *) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetTouchConfigData(unsigned int, unsigned int, unsigned int *, CUtlBuffer *, CUtlBuffer *) override {
        return unknown_ret();
    }
    virtual unknown_ret BSaveTouchConfigLayout(unsigned int, unsigned int, CUtlBuffer const *) override {
        return unknown_ret();
    }
    virtual unknown_ret BAnyControllerOptedInAndAvailible(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetTouchKeysForPopupMenu(unsigned int, unsigned int, PopupMenuTouchKey_t *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret PopupMenuTouchKeyClicked(unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret CheckMappingForEvents() override {
        return unknown_ret();
    }
    virtual unknown_ret AccessControllerInputGeneratorMouseButton(unsigned int, Voltroller::MouseButtons, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret GetEmulatedOutputState() override {
        return unknown_ret();
    }
    virtual unknown_ret GetActionSetHandle(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetActionSetHandleByTitle(unsigned int, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret StopAnalogActionMomentum(unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret StartTrackingCallback(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetControllerUsageData(unsigned int) override {
        return unknown_ret();
    }
};

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
    AdaptPassThrough(IClientControllerMap::DeactivateActionSetLayer),
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
    AdaptPassThrough(IClientControllerMap::DeactivateActionSetLayer),
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
