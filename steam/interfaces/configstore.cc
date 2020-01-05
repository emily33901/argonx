#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientConfigStore.h"
}

template <bool isServer>
class ClientConfigStore : public Reference::IClientConfigStore {
public:
    UserHandle userHandle;
    ClientConfigStore(UserHandle h) : userHandle(h) {}

    unknown_ret IsSet(EConfigStore, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetBool(EConfigStore, char const *, bool) override {
        return unknown_ret();
    }
    unknown_ret GetInt(EConfigStore, char const *, int) override {
        return unknown_ret();
    }
    unknown_ret GetUint64(EConfigStore, char const *, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret GetFloat(EConfigStore, char const *, float) override {
        return unknown_ret();
    }
    unknown_ret GetString(EConfigStore, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetBinary(EConfigStore, char const *, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetBinary(EConfigStore, char const *, CUtlBuffer *) override {
        return unknown_ret();
    }
    unknown_ret GetBinaryWatermarked(EConfigStore, char const *, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetBool(EConfigStore, char const *, bool) override {
        return unknown_ret();
    }
    unknown_ret SetInt(EConfigStore, char const *, int) override {
        return unknown_ret();
    }
    unknown_ret SetUint64(EConfigStore, char const *, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret SetFloat(EConfigStore, char const *, float) override {
        return unknown_ret();
    }
    unknown_ret SetString(EConfigStore, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetBinary(EConfigStore, char const *, unsigned char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetBinaryWatermarked(EConfigStore, char const *, unsigned char const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RemoveKey(EConfigStore, char const *) override {
        return unknown_ret();
    }
    unknown_ret GetKeySerialized(EConfigStore, char const *, unsigned char *, int) override {
        return unknown_ret();
    }
    unknown_ret FlushToDisk(bool) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientConfigStore, "SteamConfigStore");

using IClientConfigStore = ClientConfigStore<false>;
