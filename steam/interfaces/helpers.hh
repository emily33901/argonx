#pragma once

#include "platform.hh"

#include "../asyncjob.hh"
#include "../rpc.hh"

namespace Steam {
using UserHandle           = u32;
using PipeHandle           = u32;
using InterfaceConstructor = void *(*)(UserHandle h);
using InterfaceDestructor  = void (*)(void *);
typedef void *(*InstantiateInterfaceFn)(void);
} // namespace Steam

namespace Argonx {
class CMClient;
}

namespace Steam::InterfaceHelpers {
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
            Assert(*(realTarget + 1) == 0, "thisptr offset not 0 (was %p)", *(realTarget + 1));
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
    static void *                                  __Create_##name##_interfaceWithTarget(target *t) { return reinterpret_cast<void *>(new name(t)); }               \
    static void                                    __Destroy_##name##_interface(void *v) { delete reinterpret_cast<name *>(v); }                                    \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name{(Steam::InterfaceConstructor)&__Create_##name##_interface,                                     \
                                                                     interfaceName, (Steam::InterfaceDestructor)&__Destroy_##name##_interface};

#define AdaptExposeNoUser(name, target, interfaceName)                                                                                                       \
    static void *                                  __Create_##name##_interface_NoUser() { return reinterpret_cast<void *>(new name(new target())); }         \
    static void *                                  __Create_##name##_interface_NoUserWithTarget(target *t) { return reinterpret_cast<void *>(new name(t)); } \
    static void                                    __Destroy_##name##_interface_NoUser(void *v) { delete reinterpret_cast<name *>(v); }                      \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name##_NoUser{(Steam::InstantiateInterfaceFn)&__Create_##name##_interface_NoUser,            \
                                                                              interfaceName, (Steam::InterfaceDestructor)&__Destroy_##name##_interface_NoUser};

#define AdaptExposeNoUserNoTarget(name, interfaceName)                                                                                                            \
    static void *                                  __Create_##name##_interface_NoUserNoTarget() { return reinterpret_cast<void *>(new name()); }                  \
    static void                                    __Destroy_##name##_interface_NoUserNoTarget(void *v) { delete reinterpret_cast<name *>(v); }                   \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name##_NoUserNoTarget{(Steam::InstantiateInterfaceFn)&__Create_##name##_interface_NoUserNoTarget, \
                                                                                      interfaceName, (Steam::InterfaceDestructor)&__Destroy_##name##_interface_NoUserNoTarget};

#define AdaptExposeNoTarget(name, interfaceName)                                                                                                                 \
    static void *                                  __Create_##name##_interface_NoTarget(::Steam::UserHandle h) { return reinterpret_cast<void *>(new name(h)); } \
    static void                                    __Destroy_##name##_interface_NoTarget(void *v) { delete reinterpret_cast<name *>(v); }                        \
    static ::Steam::InterfaceHelpers::InterfaceReg __Register_##name##_NoTarget{(Steam::InterfaceConstructor)&__Create_##name##_interface_NoTarget,              \
                                                                                interfaceName, (Steam::InterfaceDestructor)&__Destroy_##name##_interface_NoTarget};

#define AdaptExposeClientServer(name, interfaceName)           \
    namespace {                                                \
    using name##Client = ::name<false>;                        \
    using name##Server = ::name<true>;                         \
    AdaptExposeNoTarget(name##Client, interfaceName);          \
    AdaptExposeNoTarget(name##Server, interfaceName "Server"); \
    }

#define AdaptExposeClientServerNoUser(name, interfaceName)           \
    namespace {                                                      \
    using name##Client = ::name<false>;                              \
    using name##Server = ::name<true>;                               \
    AdaptExposeNoUserNoTarget(name##Client, interfaceName);          \
    AdaptExposeNoUserNoTarget(name##Server, interfaceName "Server"); \
    }

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
    InterfaceReg(InstantiateInterfaceFn fn, const char *name, InterfaceDestructor d);
    InterfaceReg(InterfaceConstructor fn, const char *name, InterfaceDestructor d);

    bool                   requiresUser;
    InstantiateInterfaceFn create;
    InterfaceConstructor   createWithUser;
    InterfaceDestructor    destroy;
    const char *           name;

    InterfaceReg *       next; // For the global list.
    static InterfaceReg *head;
};

} // namespace Steam::InterfaceHelpers

namespace Steam {
// Helpers for Argonx:: -> Steam:: lookups
UserHandle LookupHandle(Argonx::CMClient *c);
void *     LookupInterfaceInternal(Argonx::CMClient *c, InterfaceTarget t);
template <typename T>
T *LookupInterface(Argonx::CMClient *c, InterfaceTarget t) {
    return reinterpret_cast<T *>(LookupInterfaceInternal(c, t));
}
} // namespace Steam