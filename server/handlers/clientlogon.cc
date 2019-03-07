#include <precompiled.hh>

#include "steamclient.hh"
#include "steamhandlers.hh"

#include "language_internal.hh"
#include "steammessages_clientserver_login.pb.h"

using namespace Argonx;

void ClientLogonResponseHandler(SteamClient *s, size_t msgSize, Buffer &b) {
    CMsgClientLogonResponse logonResp;
    logonResp.ParseFromArray(b.Read(0), msgSize);

    auto eresult = static_cast<EResult>(logonResp.eresult());

    printf("Logon result: %d\n", eresult);
}

RegisterHelperUnique(EMsg::ClientLogOnResponse, ClientLogonResponseHandler);