#pragma once

#include "platform.hh"

// Most of this file is taken from the open-steamworks project

// Whilst this should be "safe" to include from argonx - Can you dont please.

namespace Steam {
#define unknown_ret ::uptr

#define OBSOLETE_CALLBACK

#ifdef _WIN32
#define STEAM_CALL __cdecl
#else
#define STEAM_CALL
#endif

#if defined(__x86_64__) || defined(_WIN64)
#define X64BITS
#endif

using uint8  = ::u8;
using uint16 = ::u16;
using uint32 = ::u32;
using uint64 = ::u64;
using uintp  = ::uptr;

using int8  = ::i8;
using int16 = ::i16;
using int32 = ::i32;
using int64 = ::i64;
using intp  = ::iptr;

//
// steamclient/api
//

#include "SteamStructs/EResult.h"

// lobby type description
enum ELobbyType {
    k_ELobbyTypePrivate     = 0, // only way to join the lobby is to invite to someone else
    k_ELobbyTypeFriendsOnly = 1, // shows for friends or invitees, but not in lobby list
    k_ELobbyTypePublic      = 2, // visible for friends and in lobby list
    k_ELobbyTypeInvisible   = 3, // returned by search, but not visible to other friends
                                 //    useful if you want a user in two lobbies, for example matching groups together
                                 //	  a user can be in only one regular lobby, and up to two invisible lobbies
};

//-----------------------------------------------------------------------------
// Purpose: Possible positions to tell the overlay to show notifications in
//-----------------------------------------------------------------------------
enum ENotificationPosition {
    k_EPositionTopLeft     = 0,
    k_EPositionTopRight    = 1,
    k_EPositionBottomLeft  = 2,
    k_EPositionBottomRight = 3,
};

//-----------------------------------------------------------------------------
// Purpose: Used in ChatInfo messages - fields specific to a chat member - must fit in a uint32
//-----------------------------------------------------------------------------
enum EChatMemberStateChange {
    // Specific to joining / leaving the chatroom
    k_EChatMemberStateChangeEntered      = 0x0001, // This user has joined or is joining the chat room
    k_EChatMemberStateChangeLeft         = 0x0002, // This user has left or is leaving the chat room
    k_EChatMemberStateChangeDisconnected = 0x0004, // User disconnected without leaving the chat first
    k_EChatMemberStateChangeKicked       = 0x0008, // User kicked
    k_EChatMemberStateChangeBanned       = 0x0010, // User kicked and banned
};

enum EServerMode {
    eServerModeInvalid                 = 0, // DO NOT USE
    eServerModeNoAuthentication        = 1, // Don't authenticate user logins and don't list on the server list
    eServerModeAuthentication          = 2, // Authenticate users, list on the server list, don't run VAC on clients that connect
    eServerModeAuthenticationAndSecure = 3, // Authenticate users, list on the server list and VAC protect clients
};

// Steam universes.  Each universe is a self-contained Steam instance.
enum EUniverse {
    k_EUniverseInvalid  = 0,
    k_EUniversePublic   = 1,
    k_EUniverseBeta     = 2,
    k_EUniverseInternal = 3,
    k_EUniverseDev      = 4,
    //	k_EUniverseRC = 5, // Removed

    k_EUniverseMax
};

// these is outside NO_STEAM because external things use it
// #include "SteamStructs/ESteamError.h"
// #include "SteamStructs/ESteamNotify.h"

typedef void *(*CreateInterfaceFn)(const char *pName, int *pReturnCode);
typedef void *(*FactoryFn)(const char *pName);
typedef void *(*InstantiateInterfaceFn)(void);

typedef void (*SteamAPIWarningMessageHook_t)(int hpipe, const char *message);
typedef void (*KeyValueIteratorCallback_t)(const char *key, const char *value, void *kv);

// typedef void (*SteamNotificationCallback_t)(ESteamNotify eEvent, unsigned int nData);

typedef bool (*SteamBGetCallbackFn)(int hpipe, void *pCallbackMsg);
typedef void (*SteamFreeLastCallbackFn)(int hpipe);
typedef bool (*SteamGetAPICallResultFn)(int hpipe, uint64 hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed);

//-----------------------------------------------------------------------------
// Purpose: Passed as argument to SteamAPI_UseBreakpadCrashHandler to enable optional callback
//  just before minidump file is captured after a crash has occurred.  (Allows app to append additional comment data to the dump, etc.)
//-----------------------------------------------------------------------------
typedef void (*PFNPreMinidumpCallback)(void *context);

//-----------------------------------------------------------------------------
// Purpose: Used by ICrashHandler interfaces to reference particular installed crash handlers
//-----------------------------------------------------------------------------
typedef void *BREAKPAD_HANDLE;
#define BREAKPAD_INVALID_HANDLE (BREAKPAD_HANDLE)0

const int k_cubDigestSize = 20; // CryptoPP::SHA::DIGESTSIZE
const int k_cubSaltSize   = 8;

const int k_cchGameExtraInfoMax = 64;

// Max number of credit cards stored for one account
const int k_nMaxNumCardsPerAccount = 1;

// game server flags
const uint32 k_unServerFlagNone       = 0x00;
const uint32 k_unServerFlagActive     = 0x01; // server has users playing
const uint32 k_unServerFlagSecure     = 0x02; // server wants to be secure
const uint32 k_unServerFlagDedicated  = 0x04; // server is dedicated
const uint32 k_unServerFlagLinux      = 0x08; // linux build
const uint32 k_unServerFlagPassworded = 0x10; // password protected
const uint32 k_unServerFlagPrivate    = 0x20; // server shouldn't list on master server and
                                              // won't enforce authentication of users that connect to the server.
                                              // Useful when you run a server where the clients may not
                                              // be connected to the internet but you want them to play (i.e LANs)

//-----------------------------------------------------------------------------
// Constants used for query ports.
//-----------------------------------------------------------------------------
#define QUERY_PORT_NOT_INITIALIZED 0xFFFF // We haven't asked the GS for this query port's actual value yet.
#define QUERY_PORT_ERROR 0xFFFE           // We were unable to get the query port for this server.

typedef uint8 SHADigest_t[k_cubDigestSize];
typedef uint8 Salt_t[k_cubSaltSize];

//-----------------------------------------------------------------------------
// GID (GlobalID) stuff
// This is a globally unique identifier.  It's guaranteed to be unique across all
// racks and servers for as long as a given universe persists.
//-----------------------------------------------------------------------------
// NOTE: for GID parsing/rendering and other utils, see gid.h
typedef uint64 GID_t;

const GID_t k_GIDNil = 0xffffffffffffffffull;

// For convenience, we define a number of types that are just new names for GIDs
typedef GID_t JobID_t; // Each Job has a unique ID
typedef GID_t TxnID_t; // Each financial transaction has a unique ID

const GID_t k_TxnIDNil     = k_GIDNil;
const GID_t k_TxnIDUnknown = 0;

// this is baked into client messages and interfaces as an int,
// make sure we never break this.
typedef uint32    PackageId_t;
const PackageId_t k_uPackageIdFreeSub  = 0x0;
const PackageId_t k_uPackageIdInvalid  = 0xFFFFFFFF;
const PackageId_t k_uPackageIdWallet   = -2;
const PackageId_t k_uPackageIdMicroTxn = -3;

// this is baked into client messages and interfaces as an int,
// make sure we never break this.
typedef uint32 AppId_t;
const AppId_t  k_uAppIdInvalid             = 0x0;
const AppId_t  k_nGameIDNotepad            = 65535;
const AppId_t  k_nGameIDCSSTestApp         = 65534;
const AppId_t  k_nGameIDDRMTestApp_Static  = 6710;
const AppId_t  k_nGameIDDRMTestApp_Blob    = 6711;
const AppId_t  k_nGameIDDRMTestApp_Dynamic = 6712;
const AppId_t  k_nGameIDDRMTestApp_SDK     = 6713;
const AppId_t  k_nGameIDWinUI              = 7;
const AppId_t  k_nGameIDWinUI2             = 8;
const AppId_t  k_nGameIDCS                 = 10;
const AppId_t  k_nGameIDTFC                = 20;
const AppId_t  k_nGameIDDOD                = 30;
const AppId_t  k_nGameIDDMC                = 40;
const AppId_t  k_nGameIDOpFor              = 50;
const AppId_t  k_nGameIDRicochet           = 60;
const AppId_t  k_nGameIDHL1                = 70;
const AppId_t  k_nGameIDCZero              = 80;
const AppId_t  k_nGameIDCSBeta             = 150;
const AppId_t  k_nGameIDMacVAC             = 160;
const AppId_t  k_nGameIDWinVAC             = 202;
const AppId_t  k_nGameIDScreenshots        = 760;
const AppId_t  k_nGameDRMTest              = 199;
const AppId_t  k_nGameIDBaseSourceSDK      = 215;
const AppId_t  k_nGameIDHL2                = 220;
const AppId_t  k_nDepotHL2Buka             = 235;
const AppId_t  k_nGameIDCSS                = 240;
const AppId_t  k_nGameIDCSSBeta            = 260;
const AppId_t  k_nGameHL1SRC               = 280;
const AppId_t  k_nGameIDDODSRC             = 300;
const AppId_t  k_nGameIDHL2DM              = 320;
const AppId_t  k_nGameIDPortal             = 400;
const AppId_t  k_nGameIDHL2EP2             = 420;
const AppId_t  k_nGameIDTF2                = 440;
const AppId_t  k_nGameIDL4D                = 500;
const AppId_t  k_nGameIDL4DDemo            = 530;
const AppId_t  k_nGameIDL4D2               = 550;
const AppId_t  k_nGameIDASW                = 630;
const AppId_t  k_nGameIDTF2Staging         = 810;
const AppId_t  k_nGameIDPortal2Main        = 852;
const AppId_t  k_nGameIDPortal2            = 620;
const AppId_t  k_nGameIDASWMain            = 877;
const AppId_t  k_nGameIDDOTA               = 882;
const AppId_t  k_nGameIDASWStaging         = 886;
const AppId_t  k_nGameIDRedOrchestra       = 1200;
const AppId_t  k_nGameIDRedOrchestraBeta   = 1210;
const AppId_t  k_nGameIDKillingFloor       = 1250;
const AppId_t  k_nGameIDSin1               = 1309;
const AppId_t  k_nGameIDEarth2160          = 1900;
const AppId_t  k_nGameIDTheShip            = 2400;
const AppId_t  k_nGameIDTheShipBeta        = 2410;
const AppId_t  k_nGameIDDarkMessiahSP      = 2100;
const AppId_t  k_nGameIDDarkMessiahMPBeta  = 2110;
const AppId_t  k_nGameIDDarkMessiahMP      = 2115;
const AppId_t  k_nGameIDDarkMessiahSPDemo  = 2120;
const AppId_t  k_nGameIDDarkMessiahFix     = 2130;
const AppId_t  k_nGameRaceWTCC             = 4230;
const AppId_t  k_nGameIDLostPlanetOld      = 6500;
const AppId_t  k_nGameIDLostPlanet         = 6510;
const AppId_t  k_nGameIDNBA2K9             = 7740;
const AppId_t  k_nGameIDCallofDuty4        = 7940;
const AppId_t  k_nMLBFrontOfficeManager    = 7780;
const AppId_t  k_nGameIDMW2SP              = 10180;
const AppId_t  k_nGameIDMW2MP              = 10190;
const AppId_t  k_nGameIDIW5SP              = 42680;
const AppId_t  k_nGameIDIW5MP              = 42690;
const AppId_t  k_nGameIDCODBLOPSSP         = 42700;
const AppId_t  k_nGameIDCODBLOPSMP         = 42710;
const AppId_t  k_nGameIDEmpireTotalWar     = 10500;
const AppId_t  k_nGameCSSOnline            = 11600;
const AppId_t  k_nGameIDFirstSource        = 200;
const AppId_t  k_nGameIDLastSource         = 999;
const AppId_t  k_nGameIDFirstGoldSource    = 10;
const AppId_t  k_nGameIDLastGoldSource     = 199;
const AppId_t  k_nGameIDFirstNonSource     = 1000;
const AppId_t  k_nGameIDMax                = 2147483647;
const AppId_t  k_nGameIDStress             = 30020;
const AppId_t  k_nGameIDGCTest             = 30100;
const AppId_t  k_nAppATIDriver_Vista7_32   = 61800;
const AppId_t  k_nAppATIDriver_Vista7_64   = 61810;
const AppId_t  k_nAppATIDriver_XP_32       = 61820;
const AppId_t  k_nAppATIDriver_XP_64       = 61830;

typedef enum ShareType_t {
    SHARE_STOPIMMEDIATELY = 0,
    SHARE_RATIO           = 1,
    SHARE_MANUAL          = 2,
} ShareType_t;

typedef uint64       AssetClassId_t;
const AssetClassId_t k_ulAssetClassIdInvalid = 0x0;

typedef uint32         PhysicalItemId_t;
const PhysicalItemId_t k_uPhysicalItemIdInvalid = 0x0;

// this is baked into client messages and interfaces as an int,
// make sure we never break this.  AppIds and DepotIDs also presently
// share the same namespace, but since we'd like to change that in the future
// I've defined it seperately here.
typedef uint32  DepotId_t;
const DepotId_t k_uDepotIdInvalid = 0x0;

typedef int HVoiceCall;

// RTime32
// We use this 32 bit time representing real world time.
// It offers 1 second resolution beginning on January 1, 1970 (Unix time)
typedef uint32 RTime32;
const RTime32  k_RTime32Nil      = 0;
const RTime32  k_RTime32MinValid = 10;
const RTime32  k_RTime32Infinite = 2147483647;

typedef uint32 CellID_t;
const CellID_t k_uCellIDInvalid = 0xFFFFFFFF;

// handle to a Steam API call
typedef uint64       SteamAPICall_t;
const SteamAPICall_t k_uAPICallInvalid = 0x0;

typedef uint32 AccountID_t;

// handle to a communication pipe to the Steam client
typedef int32 HSteamPipe;
// handle to single instance of a steam user
typedef int32 HSteamUser;
// reference to a steam call, to filter results by
typedef int32 HSteamCall;

//-----------------------------------------------------------------------------
// Typedef for handle type you will receive when requesting server list.
//-----------------------------------------------------------------------------
typedef void *HServerListRequest;

// return type of GetAuthSessionTicket
typedef uint32    HAuthTicket;
const HAuthTicket k_HAuthTicketInvalid = 0;

typedef int    HNewItemRequest;
typedef uint64 ItemID;

typedef uint32 HTTPRequestHandle;

// returns true of the flags indicate that a user has been removed from the chat
#define BChatMemberStateChangeRemoved(rgfChatMemberStateChangeFlags) (rgfChatMemberStateChangeFlags & (k_EChatMemberStateChangeDisconnected | k_EChatMemberStateChangeLeft | k_EChatMemberStateChangeKicked | k_EChatMemberStateChangeBanned))

typedef void (*PFNLegacyKeyRegistration)(const char *pchCDKey, const char *pchInstallPath);
typedef bool (*PFNLegacyKeyInstalled)();

const unsigned int k_unSteamAccountIDMask       = 0xFFFFFFFF;
const unsigned int k_unSteamAccountInstanceMask = 0x000FFFFF;
// we allow 3 simultaneous user account instances right now, 1= desktop, 2 = console, 4 = web, 0 = all
const unsigned int k_unSteamUserDesktopInstance = 1;
const unsigned int k_unSteamUserConsoleInstance = 2;
const unsigned int k_unSteamUserWebInstance     = 4;

// Special flags for Chat accounts - they go in the top 8 bits
// of the steam ID's "instance", leaving 12 for the actual instances
enum EChatSteamIDInstanceFlags {
    k_EChatAccountInstanceMask = 0x00000FFF, // top 8 bits are flags

    k_EChatInstanceFlagClan     = (k_unSteamAccountInstanceMask + 1) >> 1, // top bit
    k_EChatInstanceFlagLobby    = (k_unSteamAccountInstanceMask + 1) >> 2, // next one down, etc
    k_EChatInstanceFlagMMSLobby = (k_unSteamAccountInstanceMask + 1) >> 3, // next one down, etc

    // Max of 8 flags
};

#define STEAM_USING_FILESYSTEM (0x00000001)
#define STEAM_USING_LOGGING (0x00000002)
#define STEAM_USING_USERID (0x00000004)
#define STEAM_USING_ACCOUNT (0x00000008)
#define STEAM_USING_ALL (0x0000000f)
#define STEAM_MAX_PATH (255)
#define STEAM_QUESTION_MAXLEN (255)
#define STEAM_SALT_SIZE (8)

#define STEAM_DATE_SIZE (9)
#define STEAM_TIME_SIZE (9)
#define STEAM_CARD_NUMBER_SIZE (17)
#define STEAM_CONFIRMATION_CODE_SIZE (22)
#define STEAM_CARD_HOLDERNAME_SIZE (100)
#define STEAM_CARD_APPROVAL_CODE_SIZE (100)
#define STEAM_CARD_EXPYEAR_SIZE (4)
#define STEAM_CARD_LASTFOURDIGITS_SIZE (4)
#define STEAM_CARD_EXPMONTH_SIZE (2)
#define STEAM_CARD_CVV2_SIZE (5)
#define STEAM_BILLING_ADDRESS1_SIZE (128)
#define STEAM_BILLING_ADDRESS2_SIZE (128)
#define STEAM_BILLING_CITY_SIZE (50)
#define STEAM_BILLING_ZIP_SIZE (16)
#define STEAM_BILLING_STATE_SIZE (32)
#define STEAM_BILLING_COUNTRY_SIZE (32)
#define STEAM_BILLING_PHONE_SIZE (20)
#define STEAM_BILLING_EMAIL_SIZE (100)
#define STEAM_TYPE_OF_PROOF_OF_PURCHASE_SIZE (20)
#define STEAM_PROOF_OF_PURCHASE_TOKEN_SIZE (200)
#define STEAM_EXTERNAL_ACCOUNTNAME_SIZE (100)
#define STEAM_EXTERNAL_ACCOUNTPASSWORD_SIZE (80)

#define IS_STEAM_ERROR(e) (e.eSteamError != eSteamErrorNone)

typedef unsigned int SteamHandle_t;

typedef void *SteamUserIDTicketValidationHandle_t;

typedef unsigned int SteamCallHandle_t;

#if defined(_MSC_VER)
typedef __int64          SteamSigned64_t;
typedef unsigned __int64 SteamUnsigned64_t;
#else
typedef long long          SteamSigned64_t;
typedef unsigned long long SteamUnsigned64_t;
#endif

#ifdef __cplusplus

const SteamHandle_t                       STEAM_INVALID_HANDLE                          = 0;
const SteamCallHandle_t                   STEAM_INVALID_CALL_HANDLE                     = 0;
const SteamUserIDTicketValidationHandle_t STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE = 0;
const unsigned int                        STEAM_USE_LATEST_VERSION                      = 0xFFFFFFFF;

#else

#define STEAM_INVALID_HANDLE ((SteamHandle_t)(0))
#define STEAM_INVALID_CALL_HANDLE ((SteamCallHandle_t)(0))
#define STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE ((SteamUserIDTicketValidationHandle_t)(0))
#define STEAM_USE_LATEST_VERSION (0xFFFFFFFFu);

#endif

// Each Steam instance (licensed Steam Service Provider) has a unique SteamInstanceID_t.
//
// Each Steam instance as its own DB of users.
// Each user in the DB has a unique SteamLocalUserID_t (a serial number, with possible
// rare gaps in the sequence).

typedef unsigned short SteamInstanceID_t; // MUST be 16 bits

#if defined(_MSC_VER)
typedef unsigned __int64 SteamLocalUserID_t; // MUST be 64 bits
#else
typedef unsigned long long SteamLocalUserID_t; // MUST be 64 bits
#endif

typedef char SteamPersonalQuestion_t[STEAM_QUESTION_MAXLEN + 1];

//-----------------------------------------------------------------------------
// Purpose: Base values for callback identifiers, each callback must
//			have a unique ID.
//-----------------------------------------------------------------------------
enum ECallbackType {
    k_iSteamUserCallbacks                  = 100,
    k_iSteamGameServerCallbacks            = 200,
    k_iSteamFriendsCallbacks               = 300,
    k_iSteamBillingCallbacks               = 400,
    k_iSteamMatchmakingCallbacks           = 500,
    k_iSteamContentServerCallbacks         = 600,
    k_iSteamUtilsCallbacks                 = 700,
    k_iClientFriendsCallbacks              = 800,
    k_iClientUserCallbacks                 = 900,
    k_iSteamAppsCallbacks                  = 1000,
    k_iSteamUserStatsCallbacks             = 1100,
    k_iSteamNetworkingCallbacks            = 1200,
    k_iClientRemoteStorageCallbacks        = 1300,
    k_iSteamUserItemsCallbacks             = 1400,
    k_iSteamGameServerItemsCallbacks       = 1500,
    k_iClientUtilsCallbacks                = 1600,
    k_iSteamGameCoordinatorCallbacks       = 1700,
    k_iSteamGameServerStatsCallbacks       = 1800,
    k_iSteam2AsyncCallbacks                = 1900,
    k_iSteamGameStatsCallbacks             = 2000,
    k_iClientHTTPCallbacks                 = 2100,
    k_iClientScreenshotsCallbacks          = 2200,
    k_iSteamScreenshotsCallbacks           = 2300,
    k_iClientAudioCallbacks                = 2400,
    k_iSteamUnifiedMessagesCallbacks       = 2500,
    k_iClientUnifiedMessagesCallbacks      = 2600,
    k_iClientControllerCallbacks           = 2700,
    k_iSteamControllerCallbacks            = 2800,
    k_iClientParentalSettingsCallbacks     = 2900,
    k_iClientDeviceAuthCallbacks           = 3000,
    k_iClientNetworkDeviceManagerCallbacks = 3100,
    k_iClientMusicCallbacks                = 3200,
    k_iClientRemoteClientManagerCallbacks  = 3300,
    k_iClientUGCCallbacks                  = 3400,
    k_iSteamStreamClientCallbacks          = 3500,
    k_IClientProductBuilderCallbacks       = 3600,
    k_iClientShortcutsCallbacks            = 3700,
    k_iClientRemoteControlManagerCallbacks = 3800,
    k_iSteamAppListCallbacks               = 3900,
    k_iSteamMusicCallbacks                 = 4000,
    k_iSteamMusicRemoteCallbacks           = 4100,
    k_iClientVRCallbacks                   = 4200,
    k_iClientReservedCallbacks             = 4300,
    k_iSteamReservedCallbacks              = 4400,
    k_iSteamHTMLSurfaceCallbacks           = 4500,
    k_iClientVideoCallbacks                = 4600,
    k_iClientInventoryCallbacks            = 4700,
};

// steamclient/api
// #include "CGameID.h"
// #include "CSteamID.h"

// #include "SteamStructs/ECurrencyCode.h"
// #include "SteamStructs/EVoiceResult.h"
// #include "SteamStructs/FriendGameInfo.h"
// #include "SteamStructs/MatchMakingKeyValuePair.h"
// #include "SteamStructs/gameserveritem.h"
// #include "SteamStructs/servernetadr.h"

// structure that contains client callback data
struct CallbackMsg_t {
    HSteamUser m_hSteamUser;
    int        m_iCallback;
    uint8 *    m_pubParam;
    int        m_cubParam;
};

//
// Unknown types
//
// #include "SteamStructs/EAccountType.h"
// #include "SteamStructs/EPersonaState.h"

class IConCommandBaseAccessor;
class CUtlBuffer;

template <typename T>
class CUtlMemory;

template <typename T, typename M>
class CUtlVector;

class CGameActionSet;
class CControllerMappingCreateData;
class CValidator;

struct FriendGameInfo_t;
struct COffline_OfflineLogonTicket;
struct ControllersStatus_t;
struct BindingAction_t;
struct CUtlString;
struct SteamControllerStateInternal_t;
struct PopupMenuTouchKey_t;
struct SourceGroupBindingInfo_t;
struct IconBindingData_t;
struct ActivatorInfo_t;
struct ControllerIdentity_t;
struct ControllerDetails_t;
struct ControllerPersonalizationData_t;
struct OverlayChatBrowserInfo_t;
struct ConnectedUserInfo_t;
struct EPlayerResult_t {};

// using CSteamID                          = u64;
// using CGameID                           = u64;
using EFriendAvatarSize                 = u32;
using EActivateGameOverlayToWebPageMode = u32;
using EVoiceResult                      = u32;
using ELanguage                         = u32;
using EConfigSubTree                    = u32;
using EUserNotification                 = u32;
using EConnectionPriority               = u32;
using EConnectionPriorityReason         = u32;
using EParentalFeature                  = u32;
using ECommunityPreference              = u32;
using ECurrencyCode                     = u32;
using EItemStatistic                    = u32;
using EItemPreviewType                  = u32;
using EPaymentMethod                    = u32;

using SteamControllerAppSettings_t = u64;
using EControllerConfigFeature     = u32;
using EControllerType              = u32;
using ESteamControllerPad          = u32;
using EControllerActionOrigin      = u32;
using EXboxOrigin                  = u32;
using EControllerSetting           = u32;
using EControllerSource            = u32;
using EControllerSourceMode        = u32;
using EControllerModeInput         = u32;
using EControllerActivationType    = u32;
using ESteamInputType              = u32;
using EInputActionOrigin           = u64;
using EControllerConnectionState   = u32;
using EClientUINotificationType    = u32;

using SetId          = u32;
using PresetId       = u32;
using GameActionGid  = u32;
using GroupId        = u32;
using ActivatorId    = u32;
using LayerAGroupId  = u32;
using LayerAPresetId = u32;
class CBaseGameActionSet;
class CLayerGameActionSet;
using ASetId      = u32;
using LayerASetId = u32;

namespace Voltroller {
using DigitalIO    = u32;
using MouseButtons = u32;
class ControllerSetting;
struct SteamControllerStatusEvent_t;
} // namespace Voltroller

using _EMatchMakingType_v001                    = u32;
using ISteamMatchmakingServerListResponse_v001  = void;
using ISteamMatchmakingPingResponse             = void;
using ISteamMatchmakingPlayersResponse          = void;
using ISteamMatchmakingRulesResponse            = void;
using MatchMakingKeyValuePair_t                 = void;
using _ISteamMatchmakingServerListResponse_v001 = void;

using EVRScreenshotType = u32;
using EScreenshotFile   = u32;

using EDepotBuildStatus = u32;

using EClientVRError = u32;
namespace vr {
using EVRInitError = u32;
}

struct GameNotification_t;

namespace ISteamHTMLSurface {
using EHTMLMouseButton  = u32;
using EHTMLKeyModifiers = u32;
} // namespace ISteamHTMLSurface

using EBroadcastRecorderResult = u32;
using EBroadcastPermission     = u32;

using ESteamPartyBeaconLocationType = u32;

struct SteamPartyBeaconLocation_t {
    ESteamPartyBeaconLocationType type;
    uint64                        locationID;
};
using ESteamPartyBeaconLocationData = u32;

struct AppStateInfo_s;

using ESteamTVRegionBehavior = u32;
struct SteamTVRegion_t;

using EBrowserType = u32;

enum ESteamIPType {
    k_ESteamIPTypeIPv4 = 0,
    k_ESteamIPTypeIPv6 = 1,
};

struct SteamIPAddress_t {
    union {

        uint32 m_unIPv4;       // Host order
        uint8  m_rgubIPv6[16]; // Network order! Same as inaddr_in6.  (0011:2233:4455:6677:8899:aabb:ccdd:eeff)

        // Internal use only
        uint64 m_ipv6Qword[2]; // big endian
    };

    ESteamIPType m_eType;

    bool IsSet() const {
        if (k_ESteamIPTypeIPv4 == m_eType) {
            return m_unIPv4 != 0;
        } else {
            return m_ipv6Qword[0] != 0 || m_ipv6Qword[1] != 0;
        }
    }

    static SteamIPAddress_t IPv4Any() {
        SteamIPAddress_t ipOut;
        ipOut.m_eType  = k_ESteamIPTypeIPv4;
        ipOut.m_unIPv4 = 0;

        return ipOut;
    }

    static SteamIPAddress_t IPv6Any() {
        SteamIPAddress_t ipOut;
        ipOut.m_eType        = k_ESteamIPTypeIPv6;
        ipOut.m_ipv6Qword[0] = 0;
        ipOut.m_ipv6Qword[1] = 0;

        return ipOut;
    }

    static SteamIPAddress_t IPv4Loopback() {
        SteamIPAddress_t ipOut;
        ipOut.m_eType  = k_ESteamIPTypeIPv4;
        ipOut.m_unIPv4 = 0x7f000001;

        return ipOut;
    }

    static SteamIPAddress_t IPv6Loopback() {
        SteamIPAddress_t ipOut;
        ipOut.m_eType        = k_ESteamIPTypeIPv6;
        ipOut.m_ipv6Qword[0] = 0;
        ipOut.m_ipv6Qword[1] = 0;
        ipOut.m_rgubIPv6[15] = 1;

        return ipOut;
    }
};

using ETrackQueueOrigin = u32;

using PlayingRepeat_Status = u32;
using AudioPlayback_Status = u32;

  
using EP2PSend = u32;
struct P2PSessionState_t;

using ESteamIPv6ConnectivityProtocol = u32;

// Ignore opens steamworks steamtypes.h
#define STEAMTYPES_H
#define NO_CSTEAMID_STL

#include "Open Steamworks/ESteamError.h"

#include "Open Steamworks/CGameID.h"
#include "Open Steamworks/CSteamID.h"

#include "Open Steamworks/AppsCommon.h"
#include "Open Steamworks/FriendsCommon.h"
#include "Open Steamworks/GameServerCommon.h"
#include "Open Steamworks/HTTPCommon.h"
#include "Open Steamworks/InventoryCommon.h"
#include "Open Steamworks/MatchmakingCommon.h"
#include "Open Steamworks/RemoteStorageCommon.h"

#include "Open Steamworks/UGCCommon.h"
#include "Open Steamworks/UserCommon.h"
#include "Open Steamworks/UserStatsCommon.h"
#include "Open Steamworks/UtilsCommon.h"

} // namespace Steam
