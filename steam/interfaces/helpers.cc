#include <precompiled.hh>

#include "helpers.hh"

#ifdef ARGONX_WIN
#include <Windows.h>

#elif defined(ARGONX_UNIX)

#endif

constexpr u32 allocatedSize = 100 * 0x1000;

namespace Steam::InterfaceHelpers {
TrampolineAllocator *TAllocator() {
    static TrampolineAllocator t;
    return &t;
}

TrampolineAllocator::TrampolineAllocator() {
#if defined(ARGONX_WIN)
    AllocatedMemory = (u8 *)VirtualAlloc(nullptr, allocatedSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#elif defined(ARGONX_UNIX)
    Assert(false, "Not implemented for unix.");
#endif

    offset = 0;
}

TrampolineAllocator::~TrampolineAllocator() {
#if defined(ARGONX_WIN)
    VirtualFree(AllocatedMemory, allocatedSize, MEM_RELEASE);
#elif defined(ARGONX_UNIX)
    Assert(false, "Not implemented for unix.");
#endif
}

#if defined(ARGONX_64)
// clang-format off
const u8 trampolineBasis[] = {
    // push rax
    0x50,
    // movabs rax, target
    0x48, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    // xchg rsp, rax
    0x48, 0x87, 0x04, 0x24,
    // mov rcx, [rcx+0x8]
    0x48, 0x8b, 0x49, 0x8,
    // ret
    0xC3,
};
// clang-format on

constexpr u32 trampolineAddrOffset = 3;
#else
// clang-format off
const u8 trampolineBasis[] = {
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
};
// clang-format on
constexpr u32 trampolineAddrOffset = 0;

#endif

constexpr u32 trampolineSize = sizeof(trampolineBasis);

void *TrampolineAllocator::CreateTrampoline(void *target) {
    auto allocAddr = AllocatedMemory + offset;
    offset += trampolineSize;

    // Copy the trampoline in and write the target address
    memcpy(allocAddr, trampolineBasis, trampolineSize);
    *reinterpret_cast<uptr *>(allocAddr + trampolineAddrOffset) = (uptr)target;

    return allocAddr;
}

u32 TrampolineAllocator::NumAllocated() {
    return offset / trampolineSize;
}

u32 TrampolineAllocator::BytesAllocated() {
    return offset;
}

} // namespace Steam::InterfaceHelpers
