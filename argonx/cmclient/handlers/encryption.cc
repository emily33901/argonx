#include <precompiled.hh>

#include "../cmclient.hh"
#include "../steamhandlers.hh"

#include "language_internal.hh"

#include "steammessages_clientserver_login.pb.h"

using namespace Argonx;
using namespace SteamMessageHandler;

void CMClient::HandleEncryptionRequest(CMClient *c, u32 msgSize, Buffer &request_body, u64 jobId) {
    MsgChannelEncryptRequest r;
    r.FromBuffer(request_body);
    LOG_F(INFO, "proto: %d, universe: %d", r.protocolVersion, r.universe);

    MsgBuilder w{EMsg::ChannelEncryptResponse};

    auto &b = w.GetBody();
    b.Write(MsgChannelEncryptResponse{}.ToBuffer());

    c->crypt.GenerateSessionKey(b);

    c->WriteMessage(w);
}

void CMClient::HandleEncryptionResult(CMClient *c, u32 msgSize, Buffer &b, u64 jobId) {
    MsgChannelEncryptResult r;
    r.FromBuffer(b);

    if ((EResult)r.result == EResult::OK) {
        LOG_F(INFO, "Encryption handshake successful");

        c->SetEncrypted(true);

        c->SendQueuedMessages();

    } else {
        AssertAlways(0, "Encryption handshake failed");
    }
}

RegisterHelperUnique(EMsg::ChannelEncryptRequest, CMClient::HandleEncryptionRequest);
RegisterHelperUnique(EMsg::ChannelEncryptResult, CMClient::HandleEncryptionResult);