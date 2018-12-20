#pragma once

#include "types.hh"

#include <string>
#include <vector>

#ifdef ARGONX_WIN32
#ifndef INVALID_SOCKET
typedef unsigned long long SocketInternal;
#define INVALID_SOCKET (SocketInternal)(~0)
#else
typedef SOCKET SocketInternal;
#endif
#endif

class Socket {
    SocketInternal socket;

    bool valid;

public:
    Socket(const std::string &addr, const std::string &port);

    // Blocking read functions

    u8   ReadByte();
    void Read(std::vector<u8> &output, unsigned count);
};