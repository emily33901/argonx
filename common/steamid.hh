#pragma once

#include "language.hh"
#include "types.hh"

#pragma pack(push, 1)

namespace Argonx {
struct SteamId {
    SteamId(u64 = 0) { steamId64 = 0; };
    operator u64() const { return steamId64; };

    union {
        struct {
            unsigned id : 32;
            unsigned instance : 20;
            unsigned type : 4;
            unsigned universe : 8;
        };
        u64 steamId64;
    };
};
} // namespace Argonx

#pragma pack(pop)