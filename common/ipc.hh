#pragma once

#include <functional>
#include <unordered_set>
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

    bool   isServer;
    Target id;

    // Magic is used to ensure that the client is from
    // this instance of the ipc and not a previous one
    u32 magic;

public:
    std::function<void(Pipe::Target from, u8 *data, u32 size)> processMessage;

    Pipe(bool isServer, const char *serverAddr);
    ~Pipe();

    // Processes currently waiting messages and then returns
    void ProcessMessages();

    void SendMessage(Pipe::Target h, void *data, u32 size);

    // Rewinds the buffer to base and then reads the message
    void SendMessage(Pipe::Target h, class Buffer &data);
    void SendMessage(Pipe::Target h, Buffer &&data);

    void ClientDisconnected(Pipe::Target who);

    Target Id();
};