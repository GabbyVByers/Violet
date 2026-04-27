
/*
    Socket.cpp
*/

#include "../Socket.h"
#include "../Log.h"
#include <string>

namespace Vi {

    void WinSock::init(const int major_version, const int minor_version) {
        WSAData wsa_data;
        int status = WSAStartup(MAKEWORD(major_version, minor_version), &wsa_data);
        if (status != 0) {
            Log::error("WinSock initialization failed" + std::to_string(status));
            std::terminate();
            return;
        }
        is_init_flag = true;
    }

    void WinSock::cleanup() {
        WSACleanup();
        is_init_flag = false;
    }

    bool WinSock::assert_is_init(bool crash_aggressivly) {
        if (is_init_flag) {
            return true;
        }
        else {
            static const std::string msg = "WinSock is not initialized";
            if (crash_aggressivly) {
                Log::error(msg);
                std::terminate();
            }
            Log::warning(msg);
        }
        return false;
    }
}

