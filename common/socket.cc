#include "precompiled.hh"

#include <mutex>
#include <optional>

#include "defer.hh"

#ifdef ARGONX_WIN
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <winsock2.h>

#include <iphlpapi.h>
#include <stdio.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#elif defined(ARGONX_UNIX)
#include <cstdlib>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

#include "socket.hh"

// TODO: we need a queued socket with a background thread type thing

Socket::Socket(const std::string &address, const std::string &port) {

#ifdef ARGONX_WIN
    {
        WSADATA wsaData;
        auto    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            LOG_F(ERROR, "WSAStartup failed: %d", result);
            valid = false;
            return;
        }
    }
#endif

    addrinfo hints, *addr = nullptr;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    { // Resolve the server address and port
        auto result = getaddrinfo(address.c_str(), port.c_str(), &hints, &addr);
        if (result != 0) {
            LOG_F(ERROR, "getaddrinfo failed: %d", result);

            valid = false;
            return;
        }
    }

    {
        socket = INVALID_SOCKET;

        socket = ::socket(addr->ai_family, addr->ai_socktype,
                          addr->ai_protocol);

        auto result = connect(socket, addr->ai_addr, (int)addr->ai_addrlen);
        if (result == INVALID_SOCKET) {
            // closesocket(socket);
            socket = INVALID_SOCKET;
        }

        // Should really try the next address returned by getaddrinfo
        // if the connect call failed

        freeaddrinfo(addr);

        if (socket == INVALID_SOCKET) {
            LOG_F(ERROR, "Unable to connect to server!");
            return;
        }

        valid = true;

        // u32 optvalue = 1;
        // setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&optvalue, sizeof(optvalue));
    }

    // Start the reader thread
    readThread = std::thread{[this]() { BackgroundReader(); }};
}

void Socket::BackgroundReader() {
    u8 buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    while (valid) {
        // Grab some data
        auto read = recv(socket, (char *)buffer, sizeof(buffer), 0);

        if (read == 0) {
            // Dont choke the cpu
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } else {
            // Add to the read queue
            std::lock_guard<std::mutex> lock{mutex};
            for (auto i = 0; i < read; i++)
                readQueue.push(buffer[i]);
        }
    }
}

std::optional<u8> Socket::ReadByte() {
    std::lock_guard<std::mutex> lock{mutex};
    if (readQueue.size() > 0) {
        Defer(readQueue.pop());
        return readQueue.front();
    }
    return std::nullopt;
}

bool Socket::Read(std::vector<u8> &output, unsigned count) {
    std::lock_guard<std::mutex> lock{mutex};
    output.reserve(count);

    if (readQueue.size() < count) return false;

    for (auto i = 0; i < count; i++) {
        output.push_back(readQueue.front());
        readQueue.pop();
    }

    return true;
}

bool Socket::ReadUnsafe(u8 *output, unsigned count) {
    std::lock_guard<std::mutex> lock{mutex};
    if (readQueue.size() < count) return false;

    for (unsigned i = 0; i < count; i++) {
        output[i] = readQueue.front();
        readQueue.pop();
    }

    return true;
}

void Socket::WriteUnsafe(const u8 *buffer, unsigned length) {
    std::lock_guard<std::mutex> lock{mutex};

    auto bytesSent = 0;

    while (length > 0) {
        bytesSent = send(socket, (const char *)buffer, length, 0);

        if (bytesSent == 0)
            break;
        else if (bytesSent < 0)
            break;

        buffer += bytesSent;
        length -= bytesSent;
    }

    if (length == 0) return;

    Assert(false, "Failed to correctly send all data");
}

void Socket::Write(const std::vector<u8> &bytes) {
    auto length    = bytes.size();
    auto s         = bytes.data();
    auto bytesSent = 0;

    WriteUnsafe(s, length);
}
