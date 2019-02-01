#pragma once

#include <type_traits>
#include <utility>

#include "buffer.hh"
#include "defer.hh"
#include "interfaces.hh"
#include "ipc.hh"

#include "rpcdetail.hh"

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

template <typename F>
class Rpc : public RpcBase {
    using Types               = RpcHelpers::GetRpcImpl<F>;
    using Return              = typename Types::Ret;
    using Args                = typename Types::Args;
    using RealArgs            = typename Types::RealArgs;
    using RealArgsStorage     = typename Types::RealArgsStorage;
    using Class               = typename Types::Class;
    using VirtualType         = typename Types::VirtualType;
    using OutParams           = typename Types::OutParams;
    using OutParamsNonPointer = typename Types::OutParamsNonPointer;
    using OutParamsStorage    = typename Types::OutParamsStorage;

    using Detail = typename RpcHelpers::RpcInternalDetail<F>;

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

    Return Call(Pipe::Target handle, Pipe &p) {
        Buffer b;

        Detail::WriteBufferSizes(b, args);
        Detail::WriteRealArgsToBuffer(b, args);

        if constexpr (!std::is_same_v<Return, void>) {
            Buffer r = MakeRpcCall(b, handle, p, dispatchPosition, true);

            Defer(Detail::SetOutVariables(r, args));

            return r.template Read<Return>();
        } else if constexpr (!std::is_same_v<OutParams, std::tuple<>>) {
            MakeRpcCall(b, handle, p, dispatchPosition, false);
        } else {
            MakeRpcCall(b, handle, p, dispatchPosition, true);

            Detail::SetOutVariables(r, args);
        }
    }
};

template <typename F>
Buffer Rpc<F>::DispatchFromBuffer(Class *instance, u32 functionIndex, Buffer &b) {
    auto fptr = (VirtualType)Platform::FunctionFromIndex(instance, functionIndex);

    b.SetPos(0);

    Args temp;

    RealArgsStorage  realTemp;
    OutParamsStorage outTemp;

    Detail::ReadBufferSizes(b, temp, outTemp);

    std::apply([&b](auto &... x) { (b.ReadInto(x), ...); }, realTemp);

    Detail::BuildArgs(temp, realTemp, outTemp);

    b = Buffer{};

    b.Write(std::apply([instance, fptr](auto... x) { return fptr(instance, std::forward<decltype(x)>(x)...); }, temp));

    std::apply([&b](auto &&... x) { (b.Write(x), ...); }, outTemp);

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

// struct Test {
//     virtual int Test1(int *a, bool *b, float c, int d, const char *e, u8 *f, u32 g) {
//         using namespace ::Steam;

//         Rpc<decltype(&Test::Test1)> r{this, &Test::Test1, InterfaceTarget::user};
//         r.SetArgs(a, b, c, d, e, f, g);
//         r.Call(0, *ClientPipe());
//     }

//     using T  = Steam::RpcHelpers::GetRpcImpl<decltype(&Test::Test1)>;
//     using T0 = T::OutParams;
//     using T1 = T::OutParamsNonPointer;
//     using T2 = T::Args;
//     using T3 = T::RealArgs;

//     using T4 = Steam::RpcHelpers::_OutParams<int *, bool *, float, int, const char *, u8 *, u32>::OutParams;
//     using T5 = Steam::RpcHelpers::_OutParams<int *, bool *, float, int, const char *, u8 *, u32>::RealParams;
// };

#include "defer.hh"
