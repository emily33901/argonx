#include <precompiled.hh>

#include <thread>

#include <cpptoml/include/cpptoml.h>

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

// Since this is test code we are allowing ourselves to use this
#include "../steam/interfaces/steamplatform.hh"

namespace Reference {
using namespace Steam;
#include "SteamStructs/IClientEngine.h"
#include "SteamStructs/IClientUser.h"
} // namespace Reference

int main(int argCount, char **argStrings) {
    loguru::init(argCount, argStrings);

    loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);
    loguru::add_file("latest_readable.log", loguru::Truncate, loguru::Verbosity_INFO);

    // Only show most relevant things on stderr:
    loguru::g_stderr_verbosity = 1;

    LOG_F(INFO, "Waiting for server...");

    auto *clientEngine = (Reference::IClientEngine *)Steam::CreateInterface("ClientEngine", nullptr);

    Steam::PipeHandle pipeHandle = 0;

    while (pipeHandle == 0) {
        pipeHandle = clientEngine->CreateSteamPipe();
        LOG_F(INFO, "Pipe id is %lu", pipeHandle);
    }

    auto userHandle = clientEngine->CreateLocalUser(&pipeHandle, Steam::EAccountType::k_EAccountTypeIndividual);

    bool isValid = clientEngine->IsValidHSteamUserPipe(pipeHandle, userHandle);

    LOG_F(INFO, "Are pipe and user valid: %s", isValid ? "Yes" : "No");

    auto *clientUser = (Reference::IClientUser *)clientEngine->GetIClientUser(userHandle, pipeHandle);
    LOG_F(INFO, "clientUser is null? %s", !clientUser ? "True" : "False");

    const auto cfg = cpptoml::parse_file("argonx_client.toml");

    const auto username   = cfg->get_qualified_as<std::string>("login.username");
    const auto password   = cfg->get_qualified_as<std::string>("login.password");
    const auto twofactor  = cfg->get_qualified_as<std::string>("login.twofactor");
    const auto steamguard = cfg->get_qualified_as<std::string>("login.steamguard");

    Assert(username && password && twofactor && steamguard, "client config is invalid");

    clientUser->SetTwoFactorCode(twofactor->c_str());
    clientUser->Set2ndFactorAuthCode(steamguard->c_str(), false);

    clientUser->LogOnWithPassword(username->c_str(), password->c_str());

#if 0
    std::this_thread::sleep_for(std::chrono::seconds(60));
#endif

    clientUser->BConnected();

    clientEngine->ReleaseUser(pipeHandle, userHandle);
    clientEngine->BReleaseSteamPipe(pipeHandle);
}