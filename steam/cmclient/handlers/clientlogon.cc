#include <precompiled.hh>

#include "../cmclient.hh"
#include "../steamhandlers.hh"

#include "language_internal.hh"
#include "steammessages_clientserver_login.pb.h"

using namespace Argonx;

void CMClient::ClientLogonResponseHandler(CMClient *c, size_t msgSize, Buffer &b) {
    CMsgClientLogonResponse logonResp;
    logonResp.ParseFromArray(b.Read(0), msgSize);

    auto eresult = static_cast<EResult>(logonResp.eresult());

    if (eresult == EResult::Fail) {
        c->TryAnotherCM();
    }

    printf("Logon result: %d\n", eresult);
}

RegisterHelperUnique(EMsg::ClientLogOnResponse, CMClient::ClientLogonResponseHandler);