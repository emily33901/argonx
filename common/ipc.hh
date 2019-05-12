#pragma once

#include <functional>
#include <vector>

#include "platform.hh"

#undef SendMessage

namespace zmq {
class socket_t;
class context_t;
} // namespace zmq

class Pipe {
public:
    using Target = u32;

private:
    static zmq::context_t *context;

    zmq::socket_t *sock;
    Target         id;

    std::vector<zmq::socket_t *> childSockets;

    bool isServer;

    // Used by server pipes for allocating pipes
    u32 pipeCount;
    u16 basePort;

public:
    std::function<void(Pipe::Target from, u8 *data, u32 size)> processMessage;

    Pipe(bool isServer, const char *serverAddr, u16 basePort = 0);
    ~Pipe();

    // Processes currently waiting messages and then returns
    void ProcessMessages();

    void SendMessage(Pipe::Target h, void *data, u32 size);

    u32 PipeCount();

    Target Id();
};