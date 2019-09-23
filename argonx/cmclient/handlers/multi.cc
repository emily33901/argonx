#include <precompiled.hh>

#include "../cmclient.hh"
#include "../steamhandlers.hh"

#include "language_internal.hh"
#include "steammessages_base.pb.h"

#include "zip.hh"

using namespace Argonx;

void CMClient::HandleMultiMessage(CMClient *s, u32 msgSize, Buffer &b, u64 jobId) {
    auto multi = b.ReadAsProto<CMsgMulti>(msgSize);

    auto &payload = multi.message_body();
    auto  data    = (u8 *)payload.data();

    auto sizeUnzipped = multi.size_unzipped();

    if (sizeUnzipped > 0) {
        // do the unzip...
        data = Zip::Deflate(data, payload.size(), sizeUnzipped);
    }

    auto payloadSize = sizeUnzipped ? sizeUnzipped : payload.size();

    for (unsigned offset = 0; offset < payloadSize;) {
        auto subSize = *reinterpret_cast<const u32 *>(data + offset);

        // Pretend we got a new packet and process it
        TcpPacket p;
        p.header.packetSize = subSize;

        // TODO: Dont do this data copying!
        p.body.Write(std::make_pair(data + offset + sizeof(u32), subSize));

        s->ProcessPacket(p);

        offset += sizeof(u32) + subSize;
    }

    if (sizeUnzipped > 0) {
        // Cleanup allocated memory
        delete[] data;
    }
}

RegisterHelperUnique(EMsg::Multi, CMClient::HandleMultiMessage);