#pragma once

#include "buffer.hh"
#include "emsg.hh"

#include <functional>

namespace Argonx {
class CMClient;

// Singleton deals with handling of steam messages
namespace SteamMessageHandler {
using Handler = std::function<void(CMClient *c, u32 msgSize, Buffer &b, u64 jobId)>;

void RegisterHandler(EMsg msg, const Handler &&h);
void UnregisterHandler(EMsg msg);

void ProcessMessage(CMClient *c, EMsg msg, u32 msgSize, Buffer &b, u64 jobId);

// Will automatically try to register a handler for this class on init
class RegisterHelper {
public:
    RegisterHelper(EMsg msg, const Handler &&h);
};
} // namespace SteamMessageHandler

} // namespace Argonx

#define RegisterHelperUnique(msg, handler)                                                                    \
    namespace {                                                                                               \
    static ::Argonx::SteamMessageHandler::RegisterHelper Macro_Concatenate(Handler_, __LINE__){msg, handler}; \
    }

// Helper to prevent typing the boiler-plate of a handler
#define DefineHelperHandler(handler) \
  static void handler(Argonx::CMClient *c, u32 msgSize, Buffer &b, u64 jobId)
