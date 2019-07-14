#include "precompiled.hh"

#include <random>

#include <cppzmq/zmq.hpp>

#include "buffer.hh"
#include "ipc.hh"

zmq::context_t *Pipe::context = nullptr;

static u32 CreateSocketIdentity() {
    // Something unique
    auto e = std::default_random_engine();
    e.seed(std::chrono::system_clock::now().time_since_epoch().count());

    // We cannot return "0" as a pipe handle
    u32 r;
    while (true) if (r = e() != 0) return r;
}

Pipe::Pipe(bool isServer, const char *serverAddr) : isServer(isServer) {
    if (context == nullptr) context = new zmq::context_t();

    if (isServer) {
        sock = new zmq::socket_t(*context, zmq::socket_type::router);
        try {
            sock->bind(serverAddr);
        } catch (zmq::error_t &e) {
            Assert(false, "ZMQ Error: %s\n", e.what());
        }
    } else {
        // Connect to the server as a dealer
        sock = new zmq::socket_t(*context, zmq::socket_type::dealer);

        id = CreateSocketIdentity();

        // Create an identity for ourselves
        sock->setsockopt(ZMQ_IDENTITY, id);

        try {
            sock->connect(serverAddr);
            Assert(sock->connected(), "Socket failed to connect!");
        } catch (zmq::error_t &e) {
            Assert(false, "ZMQ Error: %s\n", e.what());
        }
    }
}

Pipe::~Pipe() {
    delete sock;
}

void Pipe::ProcessMessages() {
    zmq::message_t msg;

    if (isServer) {
        while (sock->recv(&msg, ZMQ_DONTWAIT)) {
            u32 identity = *(u32 *)msg.data();

            // If we recieved a msg header then we MUST
            // recieve the body aswell
            sock->recv(&msg);
            processMessage(identity, (u8 *)msg.data(), msg.size());
        }
    } else {
        while (sock->recv(&msg, ZMQ_DONTWAIT)) {
            processMessage(0, (u8 *)msg.data(), msg.size());
        }
    }
}

void Pipe::SendMessage(Pipe::Target h, void *data, u32 size) {
    if (isServer) {
        sock->send(&h, sizeof(h), ZMQ_SNDMORE);
        sock->send(data, size);
        return;
    }

    sock->send(data, size);
}

void Pipe::SendMessage(Pipe::Target h, Buffer &b) {
    b.SetPos(0);
    SendMessage(h, b.Read(0), (u32)b.Size());
}

void Pipe::ClientDisconnected(Pipe::Target h) {
    // We dont really need to do anything here
    // But TODO: we should be the ones tracking clients!
}

Pipe::Target Pipe::Id() {
    return id;
}