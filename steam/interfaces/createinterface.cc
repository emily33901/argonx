#include <precompiled.hh>

#include "helpers.hh"

using namespace Steam::InterfaceHelpers;

InterfaceReg *InterfaceReg::head = nullptr;

InterfaceReg *GetInterfaceList() {
    return InterfaceReg::head;
}

void *CreateInterfaceInternal(const char *name, int *err) {
    InterfaceReg *cur;

    for (cur = InterfaceReg::head; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->name, name) == 0) {
            if (err) *err = 0;
            return cur->create();
        }
    }

    if (err) *err = 1;

    return nullptr;
}

#if defined(ARGONX_WIN)
__declspec(dllexport) void *CreateInterface(const char *name, int *err) {
#else
void *CreateInterface(const char *name, int *err) {
#endif
    return CreateInterfaceInternal(name, err);
}

InterfaceReg::InterfaceReg(InstantiateInterfaceFn fn, const char *name) : name(name) {
    create = fn;

    next = head;
    head = this;
}
