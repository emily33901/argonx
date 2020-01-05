
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientShader.h"
}

template <bool isServer>
class ClientShader : public Reference::IClientShader {
public:
    UserHandle userHandle;
    ClientShader(UserHandle h) : userHandle(h) {}

    unknown_ret BIsShaderManagementEnabled() override {
        return unknown_ret();
    }
    unknown_ret EnableShaderManagement(bool) override {
        return unknown_ret();
    }
    unknown_ret GetShaderDepotsTotalDiskUsage() override {
        return unknown_ret();
    }
    unknown_ret StartShaderScan(unsigned int, char const*) override {
        return unknown_ret();
    }
    unknown_ret StartPipelineBuild(unsigned int, int) override {
        return unknown_ret();
    }
    unknown_ret ProcessShaderCache(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetupShaderCacheEnvironment(char*, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret BAppHasPendingShaderContentDownload(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetAppPendingShaderDownloadSize(unsigned int) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientShader, "SteamShader");

using IClientShader = ClientShader<false>;
