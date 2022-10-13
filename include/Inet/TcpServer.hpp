//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "Socket.hpp"
#include <iostream>

class TcpServer {
public:
    TcpServer(const InetAddress& inet): m_socket(inet),
                                  m_inetAddress(inet) {
        m_socket.bindAddress();
    }

    void run() {
        m_socket.listen();

        std::string buf;

        while(1) {
            auto sock = m_socket.accept();
            while (1) {
                if(m_socket.recv(buf) <= 0) break;
                std::cout << buf;
            }
        }
    }
private:
    Socket m_socket;
    InetAddress m_inetAddress;
};