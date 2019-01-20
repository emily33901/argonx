#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

#include "Open Steamworks/UserStatsCommon.h"

namespace Reference {
#include "SteamStructs/IClientUserStats.h"
}

class IClientUserStatsMap : public Reference::IClientUserStats {
public:
    // Inherited via IClientUserStats
    virtual unknown_ret GetNumStats(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStatName(CGameID, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStatType(CGameID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumAchievements(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAchievementName(CGameID, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestCurrentStats(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStat(CGameID, char const *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetStat(CGameID, char const *, float *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetStat(CGameID, char const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetStat(CGameID, char const *, float) override {
        return unknown_ret();
    }
    virtual unknown_ret UpdateAvgRateStat(CGameID, char const *, float, double) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAchievement(CGameID, char const *, bool *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret SetAchievement(CGameID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret ClearAchievement(CGameID, char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret StoreStats(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAchievementIcon(CGameID, char const *, EGetAchievementIcon) override {
        return unknown_ret();
    }
    virtual unknown_ret BGetAchievementIconURL(CGameID, char const *, EGetAchievementIcon, char *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAchievementDisplayAttribute(CGameID, char const *, char const *, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret IndicateAchievementProgress(CGameID, char const *, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret SetMaxStatsLoaded(unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestUserStats(CSteamID, CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserStat(CSteamID, CGameID, char const *, int *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserStat(CSteamID, CGameID, char const *, float *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetUserAchievement(CSteamID, CGameID, char const *, bool *, unsigned int *) override {
        return unknown_ret();
    }
    virtual unknown_ret ResetAllStats(CGameID, bool) override {
        return unknown_ret();
    }
    virtual unknown_ret FindOrCreateLeaderboard(char const *, ELeaderboardSortMethod, ELeaderboardDisplayType) override {
        return unknown_ret();
    }
    virtual unknown_ret FindLeaderboard(char const *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLeaderboardName(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLeaderboardEntryCount(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLeaderboardSortMethod(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLeaderboardDisplayType(unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret DownloadLeaderboardEntries(unsigned long long, ELeaderboardDataRequest, int, int) override {
        return unknown_ret();
    }
    virtual unknown_ret DownloadLeaderboardEntriesForUsers(unsigned long long, CSteamID *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetDownloadedLeaderboardEntry(unsigned long long, int, LeaderboardEntry_t *, int *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret AttachLeaderboardUGC(unsigned long long, unsigned long long) override {
        return unknown_ret();
    }
    virtual unknown_ret UploadLeaderboardScore(unsigned long long, ELeaderboardUploadScoreMethod, int, int const *, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumberOfCurrentPlayers() override {
        return unknown_ret();
    }
    virtual unknown_ret GetNumAchievedAchievements(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetLastAchievementUnlocked(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMostRecentAchievementUnlocked(CGameID, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestGlobalAchievementPercentages(CGameID) override {
        return unknown_ret();
    }
    virtual unknown_ret GetMostAchievedAchievementInfo(CGameID, char *, unsigned int, float *, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetNextMostAchievedAchievementInfo(CGameID, int, char *, unsigned int, float *, bool *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetAchievementAchievedPercent(CGameID, char const *, float *) override {
        return unknown_ret();
    }
    virtual unknown_ret RequestGlobalStats(CGameID, int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGlobalStat(CGameID, char const *, long long *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGlobalStat(CGameID, char const *, double *) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGlobalStatHistory(CGameID, char const *, long long *, unsigned int) override {
        return unknown_ret();
    }
    virtual unknown_ret GetGlobalStatHistory(CGameID, char const *, double *, unsigned int) override {
        return unknown_ret();
    }
};

AdaptDeclare(ISteamUserStats001);
AdaptDefine(ISteamUserStats001, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION001") = {
    AdaptPassThrough(IClientUserStatsMap::GetNumStats),
    AdaptPassThrough(IClientUserStatsMap::GetStatName),
    AdaptPassThrough(IClientUserStatsMap::GetStatType),
    AdaptPassThrough(IClientUserStatsMap::GetNumAchievements),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementName),
    AdaptEmpty(IClientUserStatsMap::GetNumGroupAchievements),
    AdaptEmpty(IClientUserStatsMap::GetGroupAchievementName),
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptEmpty(IClientUserStatsMap::GetGroupAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptEmpty(IClientUserStatsMap::SetGroupAchievement),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptEmpty(IClientUserStatsMap::ClearGroupAchievement),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
};
AdaptDeclare(ISteamUserStats002);
AdaptDefine(ISteamUserStats002, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION002") = {
    AdaptPassThrough(IClientUserStatsMap::GetNumStats),
    AdaptPassThrough(IClientUserStatsMap::GetStatName),
    AdaptPassThrough(IClientUserStatsMap::GetStatType),
    AdaptPassThrough(IClientUserStatsMap::GetNumAchievements),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementName),
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
};
AdaptDeclare(ISteamUserStats003);
AdaptDefine(ISteamUserStats003, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION003") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
};
AdaptDeclare(ISteamUserStats004);
AdaptDefine(ISteamUserStats004, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION004") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
};
AdaptDeclare(ISteamUserStats005);
AdaptDefine(ISteamUserStats005, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION005") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
};
AdaptDeclare(ISteamUserStats006);
AdaptDefine(ISteamUserStats006, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION006") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
    AdaptPassThrough(IClientUserStatsMap::GetNumberOfCurrentPlayers),
};
AdaptDeclare(ISteamUserStats007);
AdaptDefine(ISteamUserStats007, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION007") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptEmpty(IClientUserStatsMap::GetAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptEmpty(IClientUserStatsMap::GetUserAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
    AdaptPassThrough(IClientUserStatsMap::GetNumberOfCurrentPlayers),
};
AdaptDeclare(ISteamUserStats008);
AdaptDefine(ISteamUserStats008, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION008") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptEmpty(IClientUserStatsMap::GetAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptEmpty(IClientUserStatsMap::GetUserAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
    AdaptPassThrough(IClientUserStatsMap::AttachLeaderboardUGC),
    AdaptPassThrough(IClientUserStatsMap::GetNumberOfCurrentPlayers),
};
AdaptDeclare(ISteamUserStats009);
AdaptDefine(ISteamUserStats009, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION009") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptEmpty(IClientUserStatsMap::GetAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptEmpty(IClientUserStatsMap::GetUserAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntriesForUsers),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
    AdaptPassThrough(IClientUserStatsMap::AttachLeaderboardUGC),
    AdaptPassThrough(IClientUserStatsMap::GetNumberOfCurrentPlayers),
};
AdaptDeclare(ISteamUserStats010);
AdaptDefine(ISteamUserStats010, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION010") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptEmpty(IClientUserStatsMap::GetAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptEmpty(IClientUserStatsMap::GetUserAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntriesForUsers),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
    AdaptPassThrough(IClientUserStatsMap::AttachLeaderboardUGC),
    AdaptPassThrough(IClientUserStatsMap::GetNumberOfCurrentPlayers),
    AdaptPassThrough(IClientUserStatsMap::RequestGlobalAchievementPercentages),
    AdaptPassThrough(IClientUserStatsMap::GetMostAchievedAchievementInfo),
    AdaptPassThrough(IClientUserStatsMap::GetNextMostAchievedAchievementInfo),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementAchievedPercent),
    AdaptPassThrough(IClientUserStatsMap::RequestGlobalStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, long long *), IClientUserStatsMap::GetGlobalStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, double *), IClientUserStatsMap::GetGlobalStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, long long *, unsigned int), IClientUserStatsMap::GetGlobalStatHistory),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, double *, unsigned int), IClientUserStatsMap::GetGlobalStatHistory),
};
AdaptDeclare(ISteamUserStats011);
AdaptDefine(ISteamUserStats011, IClientUserStatsMap, "STEAMUSERSTATS_INTERFACE_VERSION011") = {
    AdaptPassThrough(IClientUserStatsMap::RequestCurrentStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float *), IClientUserStatsMap::GetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, int), IClientUserStatsMap::SetStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, float), IClientUserStatsMap::SetStat),
    AdaptPassThrough(IClientUserStatsMap::UpdateAvgRateStat),
    AdaptPassThrough(IClientUserStatsMap::GetAchievement),
    AdaptPassThrough(IClientUserStatsMap::SetAchievement),
    AdaptPassThrough(IClientUserStatsMap::ClearAchievement),
    AdaptEmpty(IClientUserStatsMap::GetAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::StoreStats),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementIcon),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementDisplayAttribute),
    AdaptPassThrough(IClientUserStatsMap::IndicateAchievementProgress),
    AdaptPassThrough(IClientUserStatsMap::GetNumAchievements),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementName),
    AdaptPassThrough(IClientUserStatsMap::RequestUserStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, float *), IClientUserStatsMap::GetUserStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CSteamID, CGameID, char const *, int *), IClientUserStatsMap::GetUserStat),
    AdaptPassThrough(IClientUserStatsMap::GetUserAchievement),
    AdaptEmpty(IClientUserStatsMap::GetUserAchievementAndUnlockTime),
    AdaptPassThrough(IClientUserStatsMap::ResetAllStats),
    AdaptPassThrough(IClientUserStatsMap::FindOrCreateLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::FindLeaderboard),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardName),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardEntryCount),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardSortMethod),
    AdaptPassThrough(IClientUserStatsMap::GetLeaderboardDisplayType),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntries),
    AdaptPassThrough(IClientUserStatsMap::DownloadLeaderboardEntriesForUsers),
    AdaptPassThrough(IClientUserStatsMap::GetDownloadedLeaderboardEntry),
    AdaptPassThrough(IClientUserStatsMap::UploadLeaderboardScore),
    AdaptPassThrough(IClientUserStatsMap::AttachLeaderboardUGC),
    AdaptPassThrough(IClientUserStatsMap::GetNumberOfCurrentPlayers),
    AdaptPassThrough(IClientUserStatsMap::RequestGlobalAchievementPercentages),
    AdaptPassThrough(IClientUserStatsMap::GetMostAchievedAchievementInfo),
    AdaptPassThrough(IClientUserStatsMap::GetNextMostAchievedAchievementInfo),
    AdaptPassThrough(IClientUserStatsMap::GetAchievementAchievedPercent),
    AdaptPassThrough(IClientUserStatsMap::RequestGlobalStats),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, long long *), IClientUserStatsMap::GetGlobalStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, double *), IClientUserStatsMap::GetGlobalStat),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, long long *, unsigned int), IClientUserStatsMap::GetGlobalStatHistory),
    AdaptOverload(unknown_ret (IClientUserStatsMap::*)(CGameID, char const *, double *, unsigned int), IClientUserStatsMap::GetGlobalStatHistory),
};
