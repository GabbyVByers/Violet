
/*
    Socket.cpp
*/

#include "../Socket.h"

namespace Vi {

    void WinSock::init() {
        const int major_version = 2;
        const int minor_version = 2;
        WSAData wsa_data;
        int status = WSAStartup(MAKEWORD(major_version, minor_version), &wsa_data);
        if (status != 0) {
            Log::error("WinSock Init Failed" + std::to_string(status));
            std::terminate();
        }
    }

    void WinSock::cleanup() {
        WSACleanup();
    }
}

