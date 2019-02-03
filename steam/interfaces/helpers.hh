#pragma once

#include "platform.hh"

#include "../rpc.hh"

namespace Steam {
using UserHandle           = u32;
using PipeHandle           = u32;
using InterfaceConstructor = void *(*)(UserHandle h);
typedef void *(*InstantiateInterfaceFn)(void);
} // namespace Steam

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

        auto targetAddr = &target;

        auto realTarget = reinterpret_cast<void **>(targetAddr);

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

struct GenericAdaptor {
    void *vtable;
    void *realThisptr;
};

// For adapting versioned interfaces to their unversioned counterparts
#define AdaptDeclare(name)                            \
    struct name {                                     \
        name(void *t) { thisptr = t; }                \
        static void **functionTable;                  \
        void *        vtable_pointer = functionTable; \
        void *        thisptr;                        \
    }

#define AdaptExpose(name, target, interfaceName)                                                                                                                    \
    static void *                                  __Create_##name##_interface(::Steam::UserHandle h) { return reinterpret_cast<void *>(new name(new target(h))); } \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name{(Steam::InterfaceConstructor)&__Create_##name##_interface, interfaceName};

#define AdaptExposeNoUser(name, target, interfaceName)                                                                                               \
    static void *                                  __Create_##name##_interface_NoUser() { return reinterpret_cast<void *>(new name(new target())); } \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name##_NoUser{(Steam::InstantiateInterfaceFn)&__Create_##name##_interface_NoUser, interfaceName};

#define AdaptExposeNoUserNoTarget(name, interfaceName)                                                                                           \
    static void *                                  __Create_##name##_interface_NoUserNoTarget() { return reinterpret_cast<void *>(new name()); } \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name##_NoUserNoTarget{(Steam::InstantiateInterfaceFn)&__Create_##name##_interface_NoUserNoTarget, interfaceName};

#define AdaptDefine(name, target, interfaceName)             \
    AdaptExpose(name, target, interfaceName);                \
    extern void *name##_functionTable[];                     \
    void **      name::functionTable = name##_functionTable; \
    void *       name##_functionTable[]

#define AdaptCreateTrampoline(target) ::Steam::InterfaceHelpers::TAllocator()->CreateTrampoline(target)
#define AdaptPassThrough(target) AdaptCreateTrampoline(&target)
#define AdaptOverload(signature, target) AdaptCreateTrampoline(static_cast<signature>(&target))
#define AdaptEmpty(target) \
    AdaptCreateTrampoline(static_cast<void(PlatformThisCall *)(void *)>([](void *thisptr) -> void { Assert(0, "Attempt to call function '" #target "'\n"); }))

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
    AdaptCreateTrampoline((::Steam::InterfaceHelpers::MsvcFuck<ret(PlatformThisCall *)(TT *, PlatformEdx __VA_ARGS__)>)[](TT * thisptr, PlatformEdx __VA_ARGS__)->ret body)

class InterfaceReg {
public:
    InterfaceReg(InstantiateInterfaceFn fn, const char *name);
    InterfaceReg(InterfaceConstructor fn, const char *name);

    bool                   requiresUser;
    InstantiateInterfaceFn create;
    InterfaceConstructor   createWithUser;
    const char *           name;

    InterfaceReg *       next; // For the global list.
    static InterfaceReg *head;
};

} // namespace Steam::InterfaceHelpers
