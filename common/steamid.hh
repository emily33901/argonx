#pragma once

#include "language.hh"
#include "platform.hh"

#pragma pack(push, 1)

namespace Argonx {
struct SteamId {
    operator u64() const { return steamId64; };

    SteamId() = default;

    SteamId(const u64 x) { steamId64 = x; }

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