#pragma once

#include "platform.hh"

#include <array>
#include <mutex>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#ifdef ARGONX_WIN

#ifndef INVALID_SOCKET
typedef unsigned long long SocketInternal;
#define INVALID_SOCKET (SocketInternal)(~0)
#else
typedef SOCKET SocketInternal;
#endif

#elif defined(ARGONX_UNIX)

typedef int SocketInternal;
#define INVALID_SOCKET (SocketInternal)(~0)

#endif

class Socket {
    SocketInternal socket;

    bool valid;

    bool ReadUnsafe(u8 *buffer, unsigned count);
    void WriteUnsafe(const u8 *buffer, unsigned count);

    std::mutex mutex;

    std::queue<u8> readQueue;
    std::thread    readThread;
    void           BackgroundReader();

public:
    Socket(const std::string &addr, const std::string &port);
    Socket(std::pair<const std::string &, const std::string &> addr_port) : Socket(addr_port.first, addr_port.second) {}
    ~Socket() {
        valid = false;
        if (readThread.joinable()) readThread.join();

        // Make sure that the mutex is unlocked
        mutex.lock();
        mutex.unlock();
    }

    void operator=(Socket &&s) noexcept {
        // Stop both tasks as otherwise the old socket will
        // use the wrong mutex!
        valid = false;
        readThread.join();

        auto oldValid = s.valid;
        s.valid       = false;
        s.readThread.join();

        mutex.lock();

        // Move all of the important stuff over
        socket     = s.socket;
        valid      = oldValid;
        readQueue  = std::move(s.readQueue);
        readThread = std::thread{[this]() { BackgroundReader(); }};

        mutex.unlock();
    }

    // Non-Blocking read functions

    // You probably shouldnt use readbyte
    std::optional<u8> ReadByte();

    // Returns false if not enough data is available
    bool Read(std::vector<u8> &output, unsigned count);

    // Returns false if not enough data is available
    template <unsigned int N>
    bool Read(std::array<u8, N> arr) {
        return ReadUnsafe(&*arr.begin(), N);
    }

    // Returns false if not enough data is available
    template <typename T>
    bool ReadStructure(T &into) {
        return ReadUnsafe(reinterpret_cast<u8 *>(&into), sizeof(T) * sizeof(u8));
    }

    // TODO: Write functions are still blocking...

    template <typename T>
    void Write(const T v) {
        auto vInBytes = reinterpret_cast<const u8 *>(&v);
        WriteUnsafe(vInBytes, sizeof(T));
    }

    void Write(const std::vector<u8> &bytes);

    // TODO: provide non-blocking read/write functions
};
