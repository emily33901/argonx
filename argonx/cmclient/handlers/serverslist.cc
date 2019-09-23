#include <precompiled.hh>

#include "../cmclient.hh"
#include "../steamhandlers.hh"

#include "language_internal.hh"
#include "steammessages_base.pb.h"
#include "steammessages_clientserver.pb.h"

using namespace Argonx;
using namespace SteamMessageHandler;

void CMClient::HandleClientCMList(CMClient *c, u32 msgSize, Buffer &b, u64 jobId) {
    auto msg = b.ReadAsProto<CMsgClientCMList>(msgSize);

    // TODO: transform ips + ports into addresses and replace the cm list
}

RegisterHelperUnique(EMsg::ClientServersAvailable, CMClient::HandleClientCMList);