#include <precompiled.hh>

#include <array>

#include "steamhandlers.hh"
#include "buffer.hh"

using namespace Argonx;
using namespace SteamMessageHandler;

// All our message handlers
std::array<Handler *, EMsg_Last> msgHandlers{nullptr};

void SteamMessageHandler::RegisterHandler(EMsg msg, const Handler &&h) {
    msgHandlers[msg] = new Handler(h);
}

void SteamMessageHandler::UnregisterHandler(EMsg msg) {
    delete msgHandlers[msg];
    msgHandlers[msg] = nullptr;
}

void SteamMessageHandler::ProcessMessage(SteamClient *s, EMsg msg, size_t msgSize, Buffer &b) {
    auto handler = msgHandlers[msg];

    if (handler != nullptr) {
        return (*handler)(s, msgSize, b);
    }

    printf("No handler for emsg: %d\n", msg);
}

RegisterHelper::RegisterHelper(EMsg msg, const Handler &&h) {
    RegisterHandler(msg, std::forward<const Handler &&>(h));
}