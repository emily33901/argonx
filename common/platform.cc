#include "precompiled.hh"

#include "platform.hh"

#include "defer.hh"

u32 Platform::GetMemberFunctionIndex(void *instance, void *f) {
#ifdef ARGONX_WIN
    u8 *functionBytes = (u8 *)f;

    // In debug builds msvcs thunks on both platforms
    // are just jmps (e9...) to the virtual call thunk (ff ...)
    // On release we ignore the first jmp
    u8 *nextThunk = nullptr;
    if (functionBytes[0] == 0xE9) {
        // Debug builds
        u8 *offset    = functionBytes + 1;
        u8 *nextInstr = functionBytes + 5;

        nextThunk = (u8 *)((uptr)nextInstr + (*(u32 *)offset));
    } else if (functionBytes[0] == 0x48) {
        // Release builds
        nextThunk = functionBytes;
    } else if (functionBytes[0] == 0x8b) {
        nextThunk = functionBytes;
    }
#if defined(ARGONX_32)
    u16 callBytes = *(u16 *)(nextThunk += 2);
#elif defined(ARGONX_64)
    u16 callBytes = *(u16 *)(nextThunk += 3);
#endif
    nextThunk += 2;
    if (callBytes == 0x60ff) {
        return (*nextThunk) / sizeof(uptr);
    } else if (callBytes == 0xa0ff) {
        return (*(u32 *)nextThunk) / sizeof(uptr);
    }

#else
    // The function pointer is just the index + 1
    auto index = *(uptr *)&f;
    Assert(index & 1, "Pointer does not comply!");
    return (index - 1) / sizeof(uptr);
#endif
    AssertAlways(0, "Unknown platform");
    return 0;
}

#ifdef ARGONX_UNIX
#include <cxxabi.h>
#endif

const char *Platform::DemangleName(const char *n) {
#ifdef ARGONX_UNIX
    static char buffer[1024];

    int status = -4;

    char *result = abi::__cxa_demangle(n, nullptr, nullptr, &status);
    Defer(free(result));

    if (status != 0) Assert(0, "Unable to demangle name");

    memcpy(buffer, result, sizeof(buffer));
    return buffer;
#else

    return n;

#endif
}
