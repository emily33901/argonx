#include <precompiled.hh>

#include "steamclient.hh"
#include "steamhandlers.hh"

#include "language_internal.hh"

#include "steammessages_clientserver_login.pb.h"

using namespace Argonx;
using namespace SteamMessageHandler;

// TODO:
// These should probably be members of CMClient

void HandleEncryptionRequest(CMClient *s, size_t msgSize, Buffer &request_body) {
    MsgChannelEncryptRequest r;
    r.FromBuffer(request_body);
    printf("proto: %d, universe: %d\n", r.protocolVersion, r.universe);

    MsgBuilder w{EMsg::ChannelEncryptResponse};

    auto &b = w.GetBody();
    b.Write(MsgChannelEncryptResponse{}.ToBuffer());

    s->crypt.GenerateSessionKey(b);

    s->WriteMessage(w);
}

void HandleEncryptionResult(CMClient *s, size_t msgSize, Buffer &b) {
    MsgChannelEncryptResult r;
    r.FromBuffer(b);

    if ((EResult)r.result == EResult::OK) {
        printf("Encryption handshake successful\n");

        s->SetEncrypted(true);

        // TODO: add on handshake function

    } else {
        printf("Encryption handshake failed!\n");
        assert(0); // This should never happen
    }
}

RegisterHelperUnique(EMsg::ChannelEncryptRequest, HandleEncryptionRequest);
RegisterHelperUnique(EMsg::ChannelEncryptResult, HandleEncryptionResult);