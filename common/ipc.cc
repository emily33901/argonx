#include "precompiled.hh"
#include <cppzmq/zmq.hpp>

#include "ipc.hh"

static u32 magic = 0xF155104;

struct RequestPipeResult {
    Pipe::Target id;
    char         address[64];
};

zmq::context_t *Pipe::context = nullptr;

Pipe::Pipe(bool isServer, const char *serverAddr, u16 basePort) : isServer(isServer), pipeCount(0), basePort(basePort) {
    if (context == nullptr) context = new zmq::context_t();

    if (isServer) {
        id = 0;

        sock = new zmq::socket_t(*context, zmq::socket_type::rep);
        try {
            sock->bind(serverAddr);
        } catch (zmq::error_t &e) {
            Assert(false, "ZMQ Error: %s\n", e.what());
        }
    } else {
        // Request a new socket from server
        sock = new zmq::socket_t(*context, zmq::socket_type::req);

        try {
            sock->connect(serverAddr);
        } catch (zmq::error_t &e) {
            Assert(false, "ZMQ Error: %s\n", e.what());
        }

        sock->send(&magic, sizeof(magic));

        RequestPipeResult p;
        zmq::message_t    msg;

        auto r = sock->recv(&msg);
        Assert(r, "pipeRequest failed");

        memcpy(&p, msg.data(), sizeof(RequestPipeResult));

        delete sock;
        sock = new zmq::socket_t(*context, zmq::socket_type::pair);

        try {
            sock->connect(p.address);
        } catch (zmq::error_t &e) {
            Assert(false, "ZMQ Error: %s\n", e.what());
        }

        id = p.id;
    }
}

Pipe::~Pipe() {
    delete sock;

    for (auto &s : childSockets) {
        delete s;
    }
}

void Pipe::ProcessMessages() {
    zmq::message_t msg;

    if (isServer) {
        for (auto i = 0; i < childSockets.size(); i++) {
            auto &s = childSockets[i];
            if (s == nullptr) continue;

            while (s->recv(&msg, ZMQ_DONTWAIT)) {
                processMessage(i + 1, (u8 *)msg.data(), msg.size());
            }
        }

        while (sock->recv(&msg, ZMQ_DONTWAIT)) {
            pipeCount += 1;

            std::string newAddr = "tcp://127.0.0.1:";
            newAddr += std::to_string(basePort + pipeCount);

            auto s = new zmq::socket_t(*context, zmq::socket_type::pair);

            try {
                s->bind(newAddr.c_str());
            } catch (zmq::error_t &e) {
                Assert(false, "ZMQ Error: %s\n", e.what());
            }

            childSockets.push_back(s);
            auto handle = childSockets.size();

            auto              data = newAddr.data();
            RequestPipeResult p{static_cast<Target>(handle)};
            memcpy(&p.address, data, newAddr.size());

            sock->send(&p, sizeof(p));
        }
    } else {
        while (sock->recv(&msg, ZMQ_DONTWAIT)) {
            processMessage(0, (u8 *)msg.data(), msg.size());
        }
    }
}

void Pipe::SendMessage(Pipe::Target h, void *data, u32 size) {
    if (isServer)
        childSockets[h - 1]->send(data, size);
    else
        sock->send(data, size);
}

void Pipe::ClientDisconnected(Pipe::Target h) {
    if (isServer) {
        auto &s = childSockets[h - 1];

        delete childSockets[h - 1];
        childSockets[h - 1] = nullptr;
    }
}

u32 Pipe::PipeCount() {
    return pipeCount;
}

Pipe::Target Pipe::Id() {
    return id;
}