
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientCompat.h"
}

template <bool isServer>
class ClientCompat : public Reference::IClientCompat {
public:
    UserHandle userHandle;
    ClientCompat(UserHandle h) : userHandle(h) {}

    unknown_ret BIsCompatLayerEnabled() override {
        return unknown_ret();
    }
    unknown_ret EnableCompat(bool) override {
        return unknown_ret();
    }
    unknown_ret GetAvailableCompatTools(CUtlVector<CUtlString, CUtlMemory<CUtlString>> *) override {
        return unknown_ret();
    }
    unknown_ret SpecifyCompatTool(unsigned int, char const *, char const *, int) override {
        return unknown_ret();
    }
    unknown_ret BIsCompatibilityToolEnabled(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCompatToolName(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCompatToolMappingPriority(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCompatToolDisplayName(char const *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientCompat, "SteamCompat");

using IClientCompat = ClientCompat<false>;
