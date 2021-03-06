#pragma once

#include <type_traits>
#include <utility>

#include "buffer.hh"
#include "defer.hh"
#include "interfaces.hh"
#include "ipc.hh"
#include "platform.hh"

#include "rpcdetail.hh"

namespace Steam {

constexpr char rpcSocketAddress[] = "tcp://127.0.0.1:33901";
// Rpc conventions
// All "messages" begin with the jobId <i64>
struct RpcCallHeader {
    InterfaceTarget targetInterface;
    u32             dispatchIndex;
    u32             functionIndex;
    u32             userHandle;
};

// Results that are returned will have a matching jobId to one that
// already exists

// Other packets will have a jobId of < 0 ()
enum class RpcType : u32 {
    heartbeat,  // Sent by clients to signal that they are still active
    disconnect, // Sent by clients to signal that they have disonnected
    connect,    // Sent by clients when they connect to see if they are connected
};

struct RpcNonCallHeader {
    RpcType t;
};

// Pipes that are used for clients
// TODO: we really dont need 2 of these!
// (The answer to the above question is yes probably
// - it really depends on how steam.exe loads steamclient
// and how it interacts with it)
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
// these could be rpc jobs or just async call results

// These should only be called from the server
// calling them on the client is ill-formed
namespace JobManager {
// Get q unique jobid
i64 GetNextJobId();
i64 GetNextNonCallJobId();

// Post or fetch a result from the job match
void   PostResult(i64 jobId, Buffer &result);
bool   HasResult(i64 jobId);
Buffer FetchResult(i64 jobId);

// Make an rpc call (assumes the buffer is well formed from a call to RpcBase::MakeRpcCall())
Buffer MakeCall(Buffer &data, Pipe::Target handle, Pipe &p, bool hasReturn);
void   SetResponseTimeout(int seconds);
} // namespace JobManager

// Non-templated base for making rpc calls.
class RpcBase {
protected:
    // Target interface type
    InterfaceTarget target;

    // Index of the virtual function we are trying to call
    u32 targetIndex;

public:
    Buffer MakeRpcCall(Buffer &serializedArgs, Pipe::Target handle, Pipe &p, u32 dispatchPosition, bool hasReturn, Steam::UserHandle userHandle);
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

    Return Call(Pipe::Target handle, Pipe &p, Steam::UserHandle userHandle) {
        Buffer b;

        // Write all of the stuff that we need to send down the rpc
        Detail::WriteBuffers(b, args);
        Detail::WriteRealArgsToBuffer(b, args);
        Detail::WriteOutParams(b, args);

        if constexpr (std::is_same_v<Return, void> && std::is_same_v<OutParams, std::tuple<>>) {
            MakeRpcCall(b, handle, p, dispatchPosition, false, userHandle);
        } else {
            Buffer r = MakeRpcCall(b, handle, p, dispatchPosition, true, userHandle);

            if (r.Size() == 0) {
                // Rpc pipe broke
                if constexpr (std::is_same_v<Return, const char *>)
                    return "";
                else
                    return Return{};
            }

            Defer(Detail::SetOutVariables(r, args));

            if constexpr (std::is_same_v<Return, void>)
                return;
            else
                return r.template Read<Return>();
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

    Detail::ReadBuffers(b, temp, outTemp);

    // If you get an assert from either of these `std::apply`s then your dispatches
    // are probably out of order

    // Real params
    std::apply([&b](auto &... x) { (b.ReadInto(x), ...); }, realTemp);

    // Out params
    std::apply([&b](auto &... x) { (b.ReadInto(x), ...); }, outTemp);

    Detail::BuildArgs(temp, realTemp, outTemp);

    b = Buffer{};

    if constexpr (!std::is_same_v<Return, void>) {
        b.Write(std::apply([instance, fptr](auto... x) { return fptr(instance, PlatformEdxParam std::forward<decltype(x)>(x)...); }, temp));
    } else {
        std::apply([instance, fptr](auto... x) { return fptr(instance, PlatformEdxParam std::forward<decltype(x)>(x)...); }, temp);
    }

    std::apply([&b](auto &&... x) { (b.Write(x), ...); }, outTemp);

    Detail::FreeBuffers(temp);

    return b;
}

// TODO: there are probably much more robust ways
// of storing these dispatch functions
// than hoping that compilers put them in the same order

std::vector<std::pair<void *, const char *>> &RpcDispatches();

inline u32 MakeDispatch(void *f, const char *debugName) {
    auto name = strdup(debugName);
    RpcDispatches().push_back(std::make_pair(f, name));
    return (u32)RpcDispatches().size() - 1;
}

// On msvc .name() returns an already mangled name
template <typename F>
u32 Rpc<F>::dispatchPosition = MakeDispatch((void *)&Rpc<F>::DispatchFromBuffer, Platform::DemangleName(typeid(Rpc<F>).name()));

// Helper macros to selectively run code on the server or the client
#define RpcRunOnClient() \
    if constexpr (!isServer)

#define RpcRunOnServer() \
    if constexpr (isServer)

// Helper macros for catching when code is incorrectly called
// from the wrong binary
#define AssertServer() AssertAlways(isServer, "This function should only be called on the server!")
#define AssertClient() AssertAlways(!isServer, "This function should only be called on the client!")

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
    RpcRunOnClient() {                                                                                                                                     \
        Rpc<decltype(&std::remove_reference_t<decltype(*this)>::fname)> r{this, &std::remove_reference_t<decltype(*this)>::fname, InterfaceTarget::tname}; \
        r.SetArgs(__VA_ARGS__);                                                                                                                            \
        return r.Call(0, *::Steam::ClientPipe(), this->userHandle);                                                                                        \
    }                                                                                                                                                      \
    else

#define RpcMakeCallIfClientNoUser(fname, tname, ...)                                                                                                       \
    RpcRunOnClient() {                                                                                                                                     \
        Rpc<decltype(&std::remove_reference_t<decltype(*this)>::fname)> r{this, &std::remove_reference_t<decltype(*this)>::fname, InterfaceTarget::tname}; \
        r.SetArgs(__VA_ARGS__);                                                                                                                            \
        return r.Call(0, *::Steam::ClientPipe(), ~0);                                                                                                      \
    }                                                                                                                                                      \
    else

// Run the code block on both the server and the client
// (Server code will be run first with rpc and then the client code will be run)
#define RpcRunOnBoth(fname, tname, ...)                                                                                                                    \
    RpcRunOnClient() {                                                                                                                                     \
        Rpc<decltype(&std::remove_reference_t<decltype(*this)>::fname)> r{this, &std::remove_reference_t<decltype(*this)>::fname, InterfaceTarget::tname}; \
        r.SetArgs(__VA_ARGS__);                                                                                                                            \
        return r.Call(0, *::Steam::ClientPipe(), this->userHandle);                                                                                        \
    }

#define RpcRunOnBothNoUser(fname, tname, ...)                                                                                                              \
    RpcRunOnClient() {                                                                                                                                     \
        Rpc<decltype(&std::remove_reference_t<decltype(*this)>::fname)> r{this, &std::remove_reference_t<decltype(*this)>::fname, InterfaceTarget::tname}; \
        r.SetArgs(__VA_ARGS__);                                                                                                                            \
        return r.Call(0, *::Steam::ClientPipe(), ~0);                                                                                                      \
    }

} // namespace Steam