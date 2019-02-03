#pragma once

#include <cstdint>

#include <typeinfo>

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

#if defined(ARGONX_WIN)
#define AssertImpl(exp, message, ...)                                      \
    if (!!!(exp)) {                                                        \
        printf(__FILE__ ":%d: " #message "\n", __LINE__ - 1, __VA_ARGS__); \
        assert(0);                                                         \
        abort();                                                           \
    }
#elif defined(ARGONX_UNIX)
#define AssertImpl(exp, message, ...)                                        \
    if (!!!(exp)) {                                                          \
        _Pragma("GCC diagnostic push");                                      \
        _Pragma("GCC diagnostic ignored \"-Wformat\"");                      \
        printf(__FILE__ ":%d: " #message "\n", __LINE__ - 1, ##__VA_ARGS__); \
        assert(0);                                                           \
        abort();                                                             \
        _Pragma("GCC diagnostic pop");                                       \
    }
#endif

#if defined(_DEBUG)
#define Assert AssertImpl
#define AssertAlways AssertImpl
#else
#define Assert(exp, message, ...) assert(exp)
#define AssertAlways AssertImpl
#endif

namespace Platform {
u32 GetMemberFunctionIndex(void *instance, void *function);
template <typename F>
inline u32 GetMemberFunctionIndex(void *instance, F function) {
    // On GCC some function pointers are wide
    // becuase of the need to store the offset of the base of
    // the class instance

    auto realTarget = reinterpret_cast<void **>(&function);

    if constexpr (sizeof(F) > sizeof(uptr)) {
        // Ensure that our thisptr is going to be correct!
        // For the purposes of what we are doing this check can
        // probably be removed to speed up init time.
        // static_assert(0, "Unknown platform");
        // Assert(0, "Unknown platform");
    }

    return GetMemberFunctionIndex(instance, *realTarget);
}
inline void *FunctionFromIndex(void *instance, u32 index) {
    auto vtable = *(void ***)instance;
    return vtable[index];
}

template <typename T>
struct RemoveCvRef {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template <typename T>
using remove_cvref_t = typename RemoveCvRef<T>::type;

template <typename T>
struct BasePointerType {
    using Type = remove_cvref_t<std::remove_pointer_t<T>>;
};

template <typename T>
using pointer_base_t = typename BasePointerType<T>::Type;

template<typename T>
struct IsPair : std::false_type { };

template<typename First, typename Second>
struct IsPair<std::pair<First, Second>> : std::true_type {
    //using First = First;
    //using Second = Second;
};

template<typename T>
inline constexpr bool is_pair_v = IsPair<T>::value;

const char *DemangleName(const char *n);

template <typename T>
const char *DemangleName() {
    return DemangleName(typeid(T).name());
}
} // namespace Platform

#if defined(ARGONX_64) || defined(ARGONX_UNIX)
// On x64 both platforms use the same abi
// On unix there is no "thiscall" - the thisptr is the first arg
#define PlatformThisCall
#define PlatformEdx
#define PlatformEdxParam
#elif defined(ARGONX_WIN)
// On windows x86 passes thisptr in ecx
#define PlatformThisCall __fastcall
#define PlatformEdx void *__edx,
#define PlatformEdxParam (nullptr),
#endif
