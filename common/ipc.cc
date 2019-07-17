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
    while (true)
        if ((r = e()) != 0) return r;
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
        magic = CreateSocketIdentity();
    } else {
        // Connect to the server as a dealer
        sock = new zmq::socket_t(*context, zmq::socket_type::dealer);

        id = CreateSocketIdentity();

        // Create an identity for ourselves
        sock->setsockopt(ZMQ_IDENTITY, id);

        try {
            sock->connect(serverAddr);
        } catch (zmq::error_t &e) {
            Assert(false, "ZMQ Error: %s\n", e.what());
        }

        // The first thing we need to get from the server is the session magic
        // So block and wait for that
        u32            newMagic = 0;
        zmq::message_t msg{
            &newMagic,
            sizeof(newMagic),
        };
        sock->send(msg);
        sock->recv(&msg);
        magic = *(u32 *)msg.data();
        // recieve body (although its empty)
        sock->recv(&msg);
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

            sock->recv(&msg);
            u32 clientMagic = *(u32 *)msg.data();

            if (clientMagic != magic) {
                // New client (or old)
                if (clientMagic == 0) {
                    // Actual new client
                    SendMessage(identity, Buffer{magic});
                } else {
                    LOG_F(WARNING, "Wrong magic from client %lu", identity);
                }

                // If magic was something else then they are an old client
                // and need to try to reconnect - so give them the hard
                // shoulder
                continue;
            }

            // If we recieved a msg header then we MUST
            // recieve the body aswell
            sock->recv(&msg);
            processMessage(identity, (u8 *)msg.data(), msg.size());
        }
    } else {
        while (sock->recv(&msg, ZMQ_DONTWAIT)) {
            // First packet was the magic so get the next one now
            sock->recv(&msg);
            // TODO: do we need to check if the magic is correct?
            // (probably not)
            processMessage(0, (u8 *)msg.data(), (u32)msg.size());
        }
    }
}

void Pipe::SendMessage(Pipe::Target h, void *data, u32 size) {
    if (isServer) {
        sock->send(&h, sizeof(h), ZMQ_SNDMORE);
    }

    sock->send(&magic, sizeof(u32), ZMQ_SNDMORE);
    sock->send(data, size);
}

void Pipe::SendMessage(Pipe::Target h, Buffer &b) {
    b.SetPos(0);
    SendMessage(h, b.Read(0), (u32)b.Size());
}

void Pipe::SendMessage(Pipe::Target h, Buffer &&b) {
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