#include <precompiled.hh>

#include "buffer.hh"
#include "language_internal.hh"

using namespace Argonx;

void MsgHdr::FromBuffer(Buffer &b) {
    b.Read(msg, targetJobID, sourceJobID);
}

Buffer MsgHdr::ToBuffer() {
    return {msg, targetJobID, sourceJobID};
}

void MsgChannelEncryptRequest::FromBuffer(Buffer &b) {
    b.Read(protocolVersion, universe);
}

Buffer MsgChannelEncryptResponse::ToBuffer() {
    return {protocolVersion, keySize};
}

void MsgChannelEncryptResult::FromBuffer(Buffer &b) {
    b.ReadInto(result);
}
