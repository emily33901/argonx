#pragma once

#include "buffer.hh"

namespace CryptoPP {
class AutoSeededRandomPool;
}

namespace Argonx {
class SteamCrypt {
public:
    CryptoPP::AutoSeededRandomPool *rnd;

    u8 sessionKey[32];
    u8 publicKey;

    SteamCrypt();

    void GenerateSessionKey(Buffer &b);

    // These in / outs can probably be combined
    void SymetricEncrypt(Buffer &in, Buffer &out);
    void SymetricDecrypt(Buffer &in, Buffer &out);
};
} // namespace Argonx
