#pragma once

#include "buffer.hh"
#include "emsg.hh"

#include <functional>

namespace Argonx {
class CMClient;

// Singleton deals with handling of steam messages
namespace SteamMessageHandler {
using Handler = std::function<void(CMClient *s, size_t msgSize, Buffer &b)>;

void RegisterHandler(EMsg msg, const Handler &&h);
void UnregisterHandler(EMsg msg);

// Struct that helps convert a member function into a Handler
template <typename F>
struct MakeHandlerHelper;

template <typename R, typename C, typename... A>
struct MakeHandlerHelper<R (C::*)(A...)> {
    using F = R (C::*)(A...);
    inline Handler &&operator()(C *instance, F f) {
        return [instance, f](CMClient *s, size_t msgSize, Buffer &b) {
            return (instance->*f)(s, msgSize, b);
        };
    }
};
// Macro to more easily create a MakeHandlerHelper and call it.
#define MakeHandler(instance, f) MakeHandlerHelper<f>{}(instance, f)

void ProcessMessage(CMClient *s, EMsg msg, size_t msgSize, Buffer &b);

// Will automatically try to register a handler for this class on init
class RegisterHelper {
public:
    RegisterHelper(EMsg msg, const Handler &&h);
};
} // namespace SteamMessageHandler

} // namespace Argonx

#define RegisterHelperUnique(msg, handler)                                         \
    namespace {                                                                    \
    static ::Argonx::SteamMessageHandler::RegisterHelper h##handler{msg, handler}; \
    }