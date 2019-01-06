#include <precompiled.hh>

#include "buffer.hh"
#include "language_internal.hh"

using namespace Argonx;

void MsgHdr::FromBuffer(Buffer &b) {
    b.Read(msg, targetJobID, sourceJobID);
}

Buffer MsgHdr::ToBuffer() {
    return Buffer{msg, targetJobID, sourceJobID};
}

void MsgChannelEncryptRequest::FromBuffer(Buffer &b) {
    b.Read(protocolVersion, universe);
}

Buffer MsgChannelEncryptResponse::ToBuffer() {
    return Buffer{protocolVersion, keySize};
}

void MsgChannelEncryptResult::FromBuffer(Buffer &b) {
    b.ReadInto(result);
}
