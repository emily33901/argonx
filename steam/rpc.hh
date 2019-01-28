#pragma once

#include "buffer.hh"

#include "interfaces.hh"

#include "ipc.hh"

namespace Steam {
// Rpc conventions
// All "messages" begin with the jobId <u64>
struct RpcCallHeader {
    InterfaceTarget targetInterface;
    u32             dispatchIndex;
    u32             functionIndex;
    u32             userHandle;
};

// Results that are returned will have a matching jobId to one that
// already exists

// Other packets will have a jobId of -1 (CallResults etc...)

enum class RpcType : u32 {

};

struct RpcNonJob {
    RpcType t;
};

namespace RpcHelpers {
template <typename F>
struct GetRpcImpl;

template <typename R, typename C, typename... A>
struct GetRpcImpl<R (C::*)(A...)> {
    using Ret   = R;
    using Class = C;
    using Args  = std::tuple<Platform::remove_cvref_t<A>...>;

    using VirtualType = Ret(AdaptThisCall *)(void *instance, AdaptEdx A...);
};

template <typename F>
inline u32 GetVirtualFunctionIndex(void *instance, F function) {
    return Platform::GetMemberFunctionIndex(instance, function);
}
} // namespace RpcHelpers

// TODO: clean up job manager access

class JobManagerBase {
public:
    virtual void   PostResult(u64 jobId, Buffer &result)                                = 0;
    virtual Buffer MakeCall(Buffer &data, Pipe::Handle handle, Pipe &p, bool hasReturn) = 0;
};

JobManagerBase *Jobs();

class RpcBase {
protected:
    // Target interface type
    InterfaceTarget target;

    // Index of the virtual function we are trying to call
    u32 targetIndex;

public:
    Buffer MakeRpcCall(Buffer &serializedArgs, Pipe::Handle handle, Pipe &p, u32 dispatchPosition, bool hasReturn);
};

std::vector<std::pair<void *, const char *>> &RpcDispatches();

template <typename F>
class Rpc : public RpcBase {
    using Types = RpcHelpers::GetRpcImpl<F>;

    // Arguments to function
    typename Types::Args args;

    static u32 dispatchPosition;

public:
    Rpc(typename Types::Class *instance, F function, InterfaceTarget t) {
        target      = t;
        targetIndex = RpcHelpers::GetVirtualFunctionIndex(instance, function);

        // volatile auto thisTest = &test;
    }

    template <typename... Args>
    void SetArgs(Args &&... a) {
        args = std::forward_as_tuple<Args...>(a...);
    }

    static void DispatchFromBuffer(typename Types::Class *instance, u32 functionIndex, Buffer &b);

    typename Types::Ret Call(Pipe::Handle handle, Pipe &p) {
        Buffer b;

        if constexpr (!std::is_same_v<decltype(args), std::tuple<>>)
            std::apply([&b](auto &&... x) { (b.Write(x), ...); }, args);

        if constexpr (!std::is_same_v<typename Types::Ret, void>) {
            Buffer r = MakeRpcCall(b, handle, p, dispatchPosition, true);

            return r.template Read<typename Types::Ret>();
        } else {
            MakeRpcCall(b, handle, p, dispatchPosition, false);
        }
    }
};

// TODO: add support for returning a result / results!

template <typename F>
void Rpc<F>::DispatchFromBuffer(typename Types::Class *instance, u32 functionIndex, Buffer &b) {
    auto fptr = (typename Types::VirtualType)Platform::FunctionFromIndex(instance, functionIndex);

    b.SetPos(0);

    decltype(args) temp;

    std::apply([&b](auto &... x) { (b.ReadInto(x), ...); }, temp);
    std::apply([instance, fptr](auto... x) { fptr(instance, std::forward<decltype(x)>(x)...); }, temp);
}

inline u32 MakeDispatch(void *f, const char *debugName) {
    RpcDispatches().push_back(std::make_pair(f, debugName));
    return RpcDispatches().size() - 1;
}

template <typename F>
u32 Rpc<F>::dispatchPosition = MakeDispatch((void *)&Rpc<F>::DispatchFromBuffer, typeid(Rpc<F>).name());

} // namespace Steam

#include "defer.hh"