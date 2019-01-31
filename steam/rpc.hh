#pragma once

#include <type_traits>
#include <utility>

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

// Pipes that are used for clients
Pipe *ClientPipe();
void  SetClientPipe(Pipe *newPipe);
Pipe *ServerPipe();
void  SetServerPipe(Pipe *newPipe);

// Helpers for Rpc templating
namespace RpcHelpers {
template <typename T, typename Tuple, typename Res = std::tuple<>>
struct RemoveTHelper;

template <typename T, typename Res>
struct RemoveTHelper<T, std::tuple<>, Res> {
    using Type = Res;
};

template <typename T, typename... Ts, typename... TRes>
struct RemoveTHelper<T, std::tuple<T, Ts...>, std::tuple<TRes...>> : RemoveTHelper<T, std::tuple<Ts...>, std::tuple<TRes...>> {};

template <typename T, typename T1, typename... Ts, typename... TRes>
struct RemoveTHelper<T, std::tuple<T1, Ts...>, std::tuple<TRes...>> : RemoveTHelper<T, std::tuple<Ts...>, std::tuple<TRes..., T1>> {};

template <typename T, typename... Ts>
struct RemoveT {
    using Type = typename RemoveTHelper<T, std::tuple<Ts...>>::Type;
};

template <typename T>
struct PointerOrVoid {
    using Type = std::conditional_t<
        (std::is_pointer_v<T> && !std::is_same_v<Platform::pointer_base_t<T>, char>),
        T,
        void>;
};

template <typename... A>
struct OutParams {
    using Type = typename RemoveT<void, typename PointerOrVoid<A>::Type...>::Type;
};

template <typename F>
struct GetRpcImpl;

template <typename R, typename C, typename... A>
struct GetRpcImpl<R (C::*)(A...)> {
    using Ret   = R;
    using Class = C;
    using Args  = std::tuple<Platform::remove_cvref_t<A>...>;

    using VirtualType = Ret(PlatformThisCall *)(void *instance, PlatformEdx A...);

    using OutParam = typename OutParams<A...>::Type;
};

template <typename F>
inline u32 GetVirtualFunctionIndex(void *instance, F function) {
    return Platform::GetMemberFunctionIndex(instance, function);
}
} // namespace RpcHelpers

// Manages jobs that exist between the client and server.
namespace JobManager {
void   PostResult(u64 jobId, Buffer &result);
Buffer MakeCall(Buffer &data, Pipe::Target handle, Pipe &p, bool hasReturn);
} // namespace JobManager

// Non-templated base for making rpc calls.
class RpcBase {
protected:
    // Target interface type
    InterfaceTarget target;

    // Index of the virtual function we are trying to call
    u32 targetIndex;

public:
    Buffer MakeRpcCall(Buffer &serializedArgs, Pipe::Target handle, Pipe &p, u32 dispatchPosition, bool hasReturn);
};

// TODO: we need a way of extracting
// - "out" pointers
// - "out" buffers
// from the function type and allowing them to be returned
// through rpc.

template <typename F>
class Rpc : public RpcBase {
    using Types       = RpcHelpers::GetRpcImpl<F>;
    using Return      = typename Types::Ret;
    using Args        = typename Types::Args;
    using Class       = typename Types::Class;
    using VirtualType = typename Types::VirtualType;

    // Arguments to function
    Args args;

    static u32 dispatchPosition;

public:
    Rpc(Class *instance, F function, InterfaceTarget t) {
        target      = t;
        targetIndex = RpcHelpers::GetVirtualFunctionIndex(instance, function);
    }

    template <typename... Args>
    void SetArgs(Args &&... a) {
        args = std::forward_as_tuple<Args...>(a...);
    }

    static Buffer DispatchFromBuffer(Class *instance, u32 functionIndex, Buffer &b);

    typename Types::Ret Call(Pipe::Target handle, Pipe &p) {
        Buffer b;

        if constexpr (!std::is_same_v<Args, std::tuple<>>)
            std::apply([&b](auto &&... x) { (b.Write(x), ...); }, args);

        if constexpr (!std::is_same_v<Return, void>) {
            Buffer r = MakeRpcCall(b, handle, p, dispatchPosition, true);

            return r.template Read<Return>();
        } else {
            MakeRpcCall(b, handle, p, dispatchPosition, false);
        }
    }
};

// TODO: add support for returning a result / results!
template <typename F>
Buffer Rpc<F>::DispatchFromBuffer(Class *instance, u32 functionIndex, Buffer &b) {
    auto fptr = (VirtualType)Platform::FunctionFromIndex(instance, functionIndex);

    b.SetPos(0);

    Args temp;

    std::apply([&b](auto &... x) { (b.ReadInto(x), ...); }, temp);

    b = Buffer{};

    b.Write(std::apply([instance, fptr](auto... x) { return fptr(instance, std::forward<decltype(x)>(x)...); }, temp));

    return b;
}

// TODO: there are probably much more robust ways
// of storing these dispatch functions
// than hoping that compilers put them in the same order

std::vector<std::pair<void *, const char *>> &RpcDispatches();

inline u32 MakeDispatch(void *f, const char *debugName) {
    RpcDispatches().push_back(std::make_pair(f, debugName));
    return RpcDispatches().size() - 1;
}

// On msvc .name() returns an already mangled name
template <typename F>
u32 Rpc<F>::dispatchPosition = MakeDispatch((void *)&Rpc<F>::DispatchFromBuffer, typeid(Rpc<F>).name());

// Helper macro for making rpc dispatch calls
// Use case:
// virtual unknown_ret a() override {
//     printf("a called!\n");
//     RpcMakeCallIfClient(a, target) {
//         printf("Called a on server\n");
//         return 0;
//     }
// }
#define RpcMakeCallIfClient(fname, tname, ...)                                                                                                             \
    if constexpr (!isServer) {                                                                                                                             \
        Rpc<decltype(&std::remove_reference_t<decltype(*this)>::fname)> r{this, &std::remove_reference_t<decltype(*this)>::fname, InterfaceTarget::tname}; \
        r.SetArgs(__VA_ARGS__);                                                                                                                            \
        return r.Call(0, *::Steam::ClientPipe());                                                                                                          \
    } else

} // namespace Steam

#include "defer.hh"
