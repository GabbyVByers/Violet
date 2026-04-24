
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

    /* WinSock 2.2 */

    class Socket {
    public:
        Socket() = delete;
        Socket(const Socket&) = delete;
        Socket(Socket&&) = delete;

        static void init_winsock() {

            /* Init WinSock 2.2 */

            const int major_version = 2;
            const int minor_version = 2;
            
            WSAData wsa_data;
            int startup_status = WSAStartup(MAKEWORD(major_version, minor_version), &wsa_data);

            if (startup_status != 0) {
                Log::error("WinSock Init Failed" + std::to_string(WSAGetLastError()));
                std::terminate();
            }
        }

        static void cleanup_winsock() {
            WSACleanup();
        }
    };

    /* UDP */

    class SocketUDP {
    public:
        
        SocketUDP(std::string ip_address, uint16_t port) {

            /* Create UDP Sockets */

            const int address_family = AF_INET;
            const int socket_type = SOCK_DGRAM;
            const IPPROTO network_protocol = IPPROTO_UDP;

            sock = socket(address_family, socket_type, network_protocol);

            if (sock == INVALID_SOCKET) {
                Log::error("Create Socket Failed: " + std::to_string(WSAGetLastError()));
                std::terminate();
            }

            /* Receiving: Bind to Listening Port */

            sockaddr_in listening_port{};
            listening_port.sin_family = address_family;
            listening_port.sin_port = htons(port);
            listening_port.sin_addr.s_addr = INADDR_ANY;

            int bind_status = bind(sock, (sockaddr*)&listening_port, sizeof(listening_port));

            if (bind_status == SOCKET_ERROR) {
                Log::error("Binding Failed: " + std::to_string(WSAGetLastError()));
                std::terminate();
            }

            /* Sending: Setup Destination IP Address */

            peer_address.sin_family = address_family;
            peer_address.sin_port = htons(port);
            int address_status = inet_pton(address_family, ip_address.c_str(), &peer_address.sin_addr);

            if (address_status == 0) {
                Log::error("Invalid IP Address: " + ip_address);
                std::terminate();
            }

            if (address_status == -1) {
                Log::error("inetp_ton Failed: " + std::to_string(WSAGetLastError()));
                std::terminate();
            }
        }

        ~SocketUDP() {
            if (sock != INVALID_SOCKET)
                closesocket(sock);
        }

        SocketUDP(const SocketUDP&) = delete;
        SocketUDP(SocketUDP&&) = delete;
        
        void send_packet(const char* buffer, int size) const {

            /* Sending */

            int status = sendto(sock, buffer, size, 0, (sockaddr*)&peer_address, sizeof(peer_address));

            if (status == SOCKET_ERROR) {
                Log::error("Send Failed: " + std::to_string(WSAGetLastError()));
                std::terminate();
            }
        }

        void receive_packet(char* buffer, int size) const {

            /* Receiving */

            sockaddr_in return_address{};
            int size_sockaddr_in = sizeof(sockaddr_in);
            int bytes_received = recvfrom(sock, buffer, size, 0, (sockaddr*)&return_address, &size_sockaddr_in);

            if (bytes_received == SOCKET_ERROR) {
                Log::error("REceive Failed: " + std::to_string(WSAGetLastError()));
                std::terminate();
            }
        }

    private:

        SOCKET sock{};
        sockaddr_in peer_address{};

    };

    /* TCP */

    class SocketTCP {
    public:

    private:

    };
}

