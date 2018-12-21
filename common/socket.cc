#include "precompiled.hh"

#ifdef ARGONX_WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <winsock2.h>

#include <iphlpapi.h>
#include <stdio.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#endif

#include "socket.hh"

Socket::Socket(const std::string &address, const std::string &port) {
    {
        WSADATA wsaData;
        auto    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            printf("WSAStartup failed: %d\n", result);
            valid = false;
            return;
        }
    }

    addrinfo hints, *addr = nullptr;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    { // Resolve the server address and port
        auto result = getaddrinfo(address.c_str(), port.c_str(), &hints, &addr);
        if (result != 0) {
            printf("getaddrinfo failed: %d\n", result);
            WSACleanup();
            valid = false;
            return;
        }
    }

    {
        socket = INVALID_SOCKET;

        // Create a SOCKET for connecting to server
        socket = ::socket(addr->ai_family, addr->ai_socktype,
                          addr->ai_protocol);

        // Connect to server.
        auto result = connect(socket, addr->ai_addr, (int)addr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(socket);
            socket = INVALID_SOCKET;
        }

        // Should really try the next address returned by getaddrinfo
        // if the connect call failed
        // But for this simple example we just free the resources
        // returned by getaddrinfo and print an error message

        freeaddrinfo(addr);

        if (socket == INVALID_SOCKET) {
            printf("Unable to connect to server!\n");
            WSACleanup();
            return;
        }
    }
}

u8 Socket::ReadByte() {
    char ret;
    recv(socket, &ret, 1, 0);

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