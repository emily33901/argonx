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
        // On GCC function pointers are 16 bytes in size
        // becuase of the need to store the offset of the base of
        // the class instance

        auto realTarget = reinterpret_cast<void **>(&target);

        if constexpr (sizeof(&TrampolineAllocator::NumAllocated) > sizeof(uptr)) {
            // Ensure that our thisptr is going to be correct!
            // For the purposes of what we are doing this check can
            // probably be removed to speed up init time.
            Assert(*(realTarget + 1) == 0, "thisptr offset not 0");
        }

        return CreateTrampoline(*realTarget);
    }

    void *CreateTrampoline(void *target);

    u32 NumAllocated();
    u32 BytesAllocated();
};
// Ensuring that our trampoline allocator is initialised first
extern TrampolineAllocator *TAllocator();

// For adapting versioned interfaces to their unversioned counterparts
#define AdaptDeclare(name)                            \
    struct name {                                     \
        name(void *t) { thisptr = t; }                \
        static void **functionTable;                  \
        void *        vtable_pointer = functionTable; \
        void *        thisptr;                        \
    }

#define AdaptDefine(name)                                    \
    extern void *name##_functionTable[];                     \
    void **      name::functionTable = name##_functionTable; \
    void *       name##_functionTable[]

#define AdaptCreateTrampoline(target) ::Steam::InterfaceHelpers::TAllocator()->CreateTrampoline(target)
#define AdaptPassThrough(target) AdaptCreateTrampoline(&target)
#define AdaptOverload(signature, target) AdaptCreateTrampoline(static_cast<signature>(&target))
#define AdaptEmpty(target) \
    AdaptCreateTrampoline(static_cast<void (*)(void *)>([](void *thisptr) { Assert(0, "Attempt to call function '" #target "'\n"); }))

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
    AdaptCreateTrampoline((::Steam::InterfaceHelpers::MsvcFuck<ret (*)(TT *, __VA_ARGS__)>)[](TT * thisptr, __VA_ARGS__)->ret body)

class InterfaceReg {
public:
    InterfaceReg(InstantiateInterfaceFn fn, const char *name);

    InstantiateInterfaceFn create;
    const char *           name;

    InterfaceReg *       next; // For the global list.
    static InterfaceReg *head;
};

} // namespace Steam::InterfaceHelpers
