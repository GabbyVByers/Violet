
/*
    SocketUDP.cpp
*/

#include "../Socket.h"

namespace Vi {

    /* Constructor & Destructor */

    SocketUDP::SocketUDP() {
        sock_init();
    }

    SocketUDP::~SocketUDP() {
        sock_cleanup();
    }

    void SocketUDP::sock_init() {
        sock_cleanup();
        sock = socket(address_family, socket_type, network_protocol);
        if (sock == INVALID_SOCKET) {
            Log::error("Socket Creation Failed: " + std::to_string(WSAGetLastError()));
            std::terminate();
        }
        u_long non_blocking = 1;
        if (ioctlsocket(sock, FIONBIO, &non_blocking) == SOCKET_ERROR) {
            Log::error("Failed to Set Non-Blocking Mode: " + std::to_string(WSAGetLastError()));
            std::terminate();
        }
    }

    void SocketUDP::sock_cleanup() {
        if (sock != INVALID_SOCKET)
            closesocket(sock);
    }

    /* Configuration */

    void SocketUDP::set_listening_port(uint16_t port) {
        if (port == 0) {
            Log::warning("Attempted to Set Invalid Listening Port");
            return;
        }
        if (this->listening_port != 0) {
            Log::warning("Already Bound to Port: " + std::to_string(this->listening_port));
            return;
        }
        listening_port = port;
        sockaddr_in sockaddr_in_port{};
        sockaddr_in_port.sin_family = address_family;
        sockaddr_in_port.sin_port = htons(listening_port);
        sockaddr_in_port.sin_addr.s_addr = INADDR_ANY;
        int bind_status = bind(sock, (sockaddr*)&sockaddr_in_port, sizeof(sockaddr_in_port));
        if (bind_status == SOCKET_ERROR) {
            Log::error("Binding Failed: " + std::to_string(WSAGetLastError()));
            std::terminate();
        }
    }

    void SocketUDP::set_peer_address(std::string ip_address, uint16_t port) {
        sockaddr_in dummy{};
        int status = inet_pton(address_family, ip_address.c_str(), &dummy.sin_addr);
        if ((status == 0) || (status == -1)) {
            Log::warning("Attempted to Set Invalid Destination IP Address");
            return;
        }
        if (port == 0) {
            Log::warning("Attempted to Set Invalid Destination Port");
            return;
        }
        peer_ip_address = ip_address;
        peer_port = port;
        peer_address.sin_family = address_family;
        peer_address.sin_port = htons(peer_port);
        inet_pton(address_family, ip_address.c_str(), &peer_address.sin_addr);
        peer_address_configured = true;
    }

    /* Getters */

    uint16_t SocketUDP::get_listening_port() const {
        return listening_port;
    }

    std::string SocketUDP::get_peer_address() const {
        return peer_ip_address;
    }

    uint16_t SocketUDP::get_peer_port() const {
        return peer_port;
    }

    /* Sending & Receiving */

    void SocketUDP::send_packet(const char* buffer, int size) const {
        if (buffer == nullptr) {
            Log::warning("Buffer is nullptr");
            return;
        }
        if (size <= 0) {
            Log::warning("Invalid Buffer Size");
            return;
        }
        if (!peer_address_configured) {
            Log::warning("Destination Address is not Configured");
            return;
        }
        int status = sendto(sock, buffer, size, 0, (sockaddr*)&peer_address, sizeof(peer_address));
        if (status == SOCKET_ERROR) {
            const int error = WSAGetLastError();
            if (error == WSAEADDRNOTAVAIL) {
                Log::warning("Configured Address is Not Available");
                return;
            }
            Log::error("Send Failed: " + std::to_string(error));
            std::terminate();
        }
    }

    int SocketUDP::receive_packet(char* buffer, int size) const {
        if (buffer == nullptr) {
            Log::warning("Buffer is nullptr");
            return 0;
        }
        if (size <= 0) {
            Log::warning("Invalid Buffer Size");
            return 0;
        }
        if (listening_port == 0) {
            Log::warning("Listening Port Not Configured");
            return SOCKET_ERROR;
        }
        sockaddr_in return_address{};
        int size_sockaddr_in = sizeof(sockaddr_in);
        int bytes_received = recvfrom(sock, buffer, size, 0, (sockaddr*)&return_address, &size_sockaddr_in);
        if (bytes_received == SOCKET_ERROR) {
            const int error = WSAGetLastError();
            if (error == WSAEWOULDBLOCK) {
                return 0;
            }
            Log::error("Receive Failed: " + std::to_string(error));
            std::terminate();
        }
        return bytes_received;
    }
}

