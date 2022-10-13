//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "Socket.hpp"
#include <iostream>

class TcpServer {
public:
    TcpServer(const InetAddress& inet): m_socket(Socket::createTcpSocket(inet.getSockAddr()->sa_family)),
                                  m_inetAddress(inet) {
        m_socket.bindAddress(m_inetAddress);
    }

    void run() {
        m_socket.listen();

        char buf[1024];
        int bytes_read;

        while(1) {
            auto sock = m_socket.accept(m_inetAddress);
            while (1) {
                bytes_read = recv(sock, buf, 1024, 0);
                if (bytes_read <= 0) break;
                std::cout << buf;
            }
        }
    }
private:
    Socket m_socket;
    InetAddress m_inetAddress;
};