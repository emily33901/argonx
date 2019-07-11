#include "precompiled.hh"

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
            printf("WSAStartup failed: %d\n", result);
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
            printf("getaddrinfo failed: %d\n", result);

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
            printf("Unable to connect to server!\n");
            return;
        }
    }
}

u8 Socket::ReadByte() {
    char ret;

    while (auto read = recv(socket, &ret, 1, 0) != 1) {
    }

    return ret;
}

void Socket::Read(std::vector<u8> &output, unsigned count) {
    output.resize(count, 0);

    for (auto &x : output) {
        x = ReadByte();
    }
}

void Socket::ReadUnsafe(u8 *output, unsigned count) {
    for (unsigned i = 0; i < count; i++) {
        output[i] = ReadByte();
    }
}

void Socket::WriteUnsafe(const u8 *buffer, unsigned length) {
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

    Assert(0, "Failed to correctly send all data");
}

void Socket::Write(const std::vector<u8> &bytes) {
    auto length    = bytes.size();
    auto s         = bytes.data();
    auto bytesSent = 0;

    WriteUnsafe(s, length);
}
