#include "precompiled.hh"

#include "platform.hh"

u32 Platform::GetMemberFunctionIndex(void *instance, void *f) {
#ifdef ARGONX_WIN
    u8 *functionBytes = (u8 *)f;
    // Msvcs thunks on both platforms are just jmps (e9...)
    // To the virtual call thunk (ff ...)
    if (functionBytes[0] == 0xE9) {
        u8 *offset    = functionBytes + 1;
        u8 *nextInstr = functionBytes + 5;

        u8 *nextThunk = (u8 *)((uptr)nextInstr + (*(u32 *)offset));

#if defined(ARGONX_32)
        u16 callBytes = *(u16 *)(nextThunk += 2);
#elif defined(ARGONX_64)
        u16 callBytes = *(u16 *)(nextThunk += 3);
#endif
        nextThunk += 2;
        if (callBytes == 0x60ff) {
            return *nextThunk;
        } else if (callBytes == 0xa0ff) {
            return *(u32 *)nextThunk;
        }
    }
#else
    // The function pointer is just the index + 1
    auto index = *(uptr *)&f;
    Assert(index & 1, "Pointer does not comply!");
    return (index - 1) / sizeof(uptr);
#endif
    return 0;
}
