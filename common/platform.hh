#pragma once

#include <cstdint>

using u8   = std::uint8_t;
using u16  = std::uint16_t;
using u32  = std::uint32_t;
using u64  = std::uint64_t;
using uptr = std::uintptr_t;

using i8   = std::int8_t;
using i16  = std::int16_t;
using i32  = std::int32_t;
using i64  = std::int64_t;
using iptr = std::intptr_t;

#if defined(_DEBUG) && defined(ARGONX_WIN)
#define Assert(exp, message, ...)                                          \
    if (!!!(exp)) {                                                        \
        printf(__FILE__ ":%d: " #message "\n", __LINE__ - 1, __VA_ARGS__); \
        assert(0);                                                         \
    }
#elif defined(_DEBUG) && defined(ARGONX_UNIX)
#define Assert(exp, message, ...)                            \
    _Pragma("GCC diagnostic push")                           \
        _Pragma("GCC diagnostic ignored \"-Wunused-value\"") \
            assert((message, exp));                          \
    _Pragma("GCC diagnostic pop")
#else
#define Assert(exp, message, ...) assert(exp)
#endif
