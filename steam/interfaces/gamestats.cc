#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientGameStats.h"
}

template <bool isServer>
class ClientGameStats : public Reference::IClientGameStats {
public:
    UserHandle userHandle;
    ClientGameStats(UserHandle h) : userHandle(h) {}

    unknown_ret GetNewSession(signed char, unsigned long long, int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret EndSession(unsigned long long, unsigned int, short) override {
        return unknown_ret();
    }
    unknown_ret AddSessionAttributeInt(unsigned long long, char const *, int) override {
        return unknown_ret();
    }
    unknown_ret AddSessionAttributeString(unsigned long long, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddSessionAttributeFloat(unsigned long long, char const *, float) override {
        return unknown_ret();
    }
    unknown_ret AddNewRow(unsigned long long *, unsigned long long, char const *) override {
        return unknown_ret();
    }
    unknown_ret CommitRow(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret CommitOutstandingRows(unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret AddRowAttributeInt(unsigned long long, char const *, int) override {
        return unknown_ret();
    }
    unknown_ret AddRowAttributeString(unsigned long long, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret AddRowAttributeFloat(unsigned long long, char const *, float) override {
        return unknown_ret();
    }
    unknown_ret AddSessionAttributeInt64(unsigned long long, char const *, long long) override {
        return unknown_ret();
    }
    unknown_ret AddRowAttributeInt64(unsigned long long, char const *, long long) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientGameStats, "SteamGameStats");

using IClientGameStats = ClientGameStats<false>;

AdaptDeclare(ISteamGameStats001);
AdaptDefine(ISteamGameStats001, IClientGameStats, "SteamGameStats001") = {
    AdaptPassThrough(IClientGameStats::GetNewSession),
    AdaptPassThrough(IClientGameStats::EndSession),
    AdaptPassThrough(IClientGameStats::AddSessionAttributeInt),
    AdaptPassThrough(IClientGameStats::AddSessionAttributeString),
    AdaptPassThrough(IClientGameStats::AddSessionAttributeFloat),
    AdaptPassThrough(IClientGameStats::AddNewRow),
    AdaptPassThrough(IClientGameStats::CommitRow),
    AdaptPassThrough(IClientGameStats::CommitOutstandingRows),
    AdaptPassThrough(IClientGameStats::AddRowAttributeInt),
    AdaptPassThrough(IClientGameStats::AddRowAttributeString),
    AdaptPassThrough(IClientGameStats::AddRowAttributeFloat),
    AdaptPassThrough(IClientGameStats::AddSessionAttributeInt64),
    AdaptPassThrough(IClientGameStats::AddRowAttributeInt64),
};
