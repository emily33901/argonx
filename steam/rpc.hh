#pragma once

#include "Buffer.hh"

#include "interfaces.hh"

#include "ipc.hh"

namespace Steam {

namespace RpcHelpers {
template <typename F>
struct GetRpcImpl;

template <typename R, typename C, typename... A>
struct GetRpcImpl<R (C::*)(A...)> {
    using Ret   = R;
    using Class = C;
    using Args  = std::tuple<A...>;
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
    Buffer MakeRpcCall(Buffer &serializedArgs, Pipe::Handle handle, Pipe &p, bool hasReturn);
};

template <typename F>
class Rpc : public RpcBase {
    using Types = RpcHelpers::GetRpcImpl<F>;

    // Arguments to function
    typename Types::Args args;

public:
    Rpc(typename Types::Class *instance, F function, InterfaceTarget t) {
        target      = t;
        targetIndex = RpcHelpers::GetVirtualFunctionIndex(instance, function);
    }

    void SetArgs(typename Types::Args &&a) {
        args(std::forward<typename Types::Args &&>(a));
    }

    typename Types::Ret Call(Pipe::Handle handle, Pipe &p) {
        Buffer b;

        if constexpr (!std::is_same_v<decltype(args), std::tuple<>>)
            std::apply([&b](auto &&x) { b.Write(x); }, args);

        if constexpr (!std::is_same_v<typename Types::Ret, void>)
            return MakeRpcCall(b, handle, p, true).Read<typename Types::Ret>();
        else
            MakeRpcCall(b, handle, p, false);
    }
};
} // namespace Steam