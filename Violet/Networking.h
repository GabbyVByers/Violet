
/*
    Networking.h
*/

#pragma once

#include "Logging.h"
#include <string>
#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winsock2.h>
#include <ws2tcpip.h>

#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif

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
    private:
        friend SocketUDP;
        friend SocketTCP;
        static inline size_t counter{};
        static void inc_socket_counter();
        static void dec_socket_counter();
    };

    class SocketUDP {
    public:
        SocketUDP();
        SocketUDP(const SocketUDP&) = delete;
        SocketUDP(SocketUDP&&) = delete;
        ~SocketUDP();
        void config_listening_port(uint16_t);
        void config_destination_address(std::string, uint16_t);
        uint16_t query_listening_port() const;
        std::string query_destination_address() const;
        uint16_t query_destination_port() const;
        void send_packet(const char* buffer, int size) const;
        int receive_packet(char* buffer, int size) const;
    private:
        SOCKET sock = INVALID_SOCKET;
        uint16_t listening_port{};
        bool destination_address_configured = false;
        uint16_t destination_port{};
        std::string destination_ip_address_string{};
        sockaddr_in destination_address{};
        const int address_family = AF_INET;
        const int socket_type = SOCK_DGRAM;
        const IPPROTO network_protocol = IPPROTO_UDP;
    };

    class SocketTCP {};
}

