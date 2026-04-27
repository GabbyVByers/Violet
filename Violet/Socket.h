
/*
    Socket.h
*/

#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#include <string>
#include <cstdint>
#include "Log.h"

#define Vi Vi
namespace Vi {

    class WinSock;
    class SocketUDP;
    class SocketTCP;

    class WinSock {
    public:
        WinSock() = delete;
        WinSock(const WinSock&) = delete;
        WinSock(WinSock&&) = delete;
        static void init(int = 2, int = 2);
        static void cleanup();
    private:
        friend SocketUDP;
        friend SocketTCP;
        static inline bool is_init_flag = false;
        static bool assert_is_init(bool = false);
    };

    class SocketUDP {
    public:
        SocketUDP();
        SocketUDP(const SocketUDP&) = delete;
        SocketUDP(SocketUDP&&) = delete;
        ~SocketUDP();
        void set_listening_port(uint16_t);
        void set_peer_address(std::string, uint16_t);
        uint16_t get_listening_port() const;
        std::string get_peer_address() const;
        uint16_t get_peer_port() const;
        void send_packet(const char* buffer, int size) const;
        int receive_packet(char* buffer, int size) const;
    private:
        SOCKET sock = INVALID_SOCKET;
        uint16_t listening_port = 0;
        bool peer_address_configured = false;
        uint16_t peer_port = 0;
        std::string peer_ip_address{};
        sockaddr_in peer_address{};
        const int address_family = AF_INET;
        const int socket_type = SOCK_DGRAM;
        const IPPROTO network_protocol = IPPROTO_UDP;
    };

    class SocketTCP {};
}

