#pragma once

#include "platform.hh"

namespace Steam {
typedef void *(*InstantiateInterfaceFn)(void);
}

namespace Steam::InterfaceHelpers {
// Arena allocator but for creating trampoline functions
class TrampolineAllocator {
    u8 * allocatedMemory;
    uptr offset;

public:
    TrampolineAllocator();
    ~TrampolineAllocator();

    template <typename F>
    void *CreateTrampoline(F target) {
        // On GCC some function pointers are 16 bytes in size
        // becuase of the need to store the offset of the base of
        // the class instance

        auto realTarget = reinterpret_cast<void **>(&target);

        if constexpr (sizeof(F) > sizeof(uptr)) {
            // Ensure that our thisptr is going to be correct!
            // For the purposes of what we are doing this check can
            // probably be removed to speed up init time.
            Assert(*(realTarget + 1) == 0, "thisptr offset not 0 (was %d)", *(realTarget + 1));
        }

        return CreateTrampoline(*realTarget);
    }

    void *CreateTrampoline(void *target);

    u32 NumAllocated();
    u32 BytesAllocated();
};
// Ensuring that our trampoline allocator is initialised first
extern TrampolineAllocator *TAllocator();

#if defined(ARGONX_64) || defined(ARGONX_UNIX)
// On x64 both platforms use the same abi
// On unix there is no "thiscall" - the thisptr is the first arg
#define AdaptThisCall
#elif defined(ARGONX_WIN)
// On windows x86 passes thisptr in ecx
#define AdaptThisCall __thiscall
#endif

// For adapting versioned interfaces to their unversioned counterparts
#define AdaptDeclare(name)                            \
    struct name {                                     \
        name(void *t) { thisptr = t; }                \
        static void **functionTable;                  \
        void *        vtable_pointer = functionTable; \
        void *        thisptr;                        \
    }

#define AdaptExpose(name, target, interfaceName)                                                                                              \
    static void *                                  __Create_##name##_interface() { return reinterpret_cast<void *>(new name(new target())); } \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name{&__Create_##name##_interface, interfaceName};

#define AdaptDefine(name, target, interfaceName)             \
    AdaptExpose(name, target, interfaceName);                \
    extern void *name##_functionTable[];                     \
    void **      name::functionTable = name##_functionTable; \
    void *       name##_functionTable[]

#define AdaptCreateTrampoline(target) ::Steam::InterfaceHelpers::TAllocator()->CreateTrampoline(target)
#define AdaptPassThrough(target) AdaptCreateTrampoline(&target)
#define AdaptOverload(signature, target) AdaptCreateTrampoline(static_cast<signature>(&target))
#define AdaptEmpty(target) \
    AdaptCreateTrampoline(static_cast<void(AdaptThisCall *)(void *)>([](void *thisptr) { Assert(0, "Attempt to call function '" #target "'\n"); }))

// Helper for msvcs type parsing
template <typename T>
using MsvcFuck = T;

// Lambda wont convert to function easily
// so we have to apply a little *coercion*

// This macro is ugly but the args have to be in this order
// to allow any number of args to the function without writing a
// large amount of macro bollocks
// used like `AdaptCustom(Test2, int, { return thisptr->Test(b, a); }, int a, int b)`
#define AdaptCustom(TT, ret, body, ...) \
    AdaptCreateTrampoline((::Steam::InterfaceHelpers::MsvcFuck<ret(AdaptThisCall *)(TT *, __VA_ARGS__)>)[](TT * thisptr, __VA_ARGS__)->ret body)

class InterfaceReg {
public:
    InterfaceReg(InstantiateInterfaceFn fn, const char *name);

    InstantiateInterfaceFn create;
    const char *           name;

    InterfaceReg *       next; // For the global list.
    static InterfaceReg *head;
};

} // namespace Steam::InterfaceHelpers
