#pragma once

#include "buffer.hh"
#include "emsg.hh"

#include <functional>

namespace Argonx {
class SteamClient;

// Singleton deals with handling of steam messages
namespace SteamMessageHandler {
using Handler = std::function<void(SteamClient *s, size_t msgSize, Buffer &b)>;

void RegisterHandler(EMsg msg, const Handler &&h);
void UnregisterHandler(EMsg msg);

void ProcessMessage(SteamClient *s, EMsg msg, size_t msgSize, Buffer &b);

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