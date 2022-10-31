//
// Created by egor on 10/25/22.
//

#include "TcpConnection.hpp"
#include <iostream>

TcpConnection::TcpConnection(int fd) {
    m_socket = std::make_unique<Socket>(fd);
}

void TcpConnection::send(const char *msg, std::size_t len) {
    auto result = ::send(m_socket->fd(), msg, len, 0);
    std::cout << "Result: " << result << '\n';
}

TcpConnection::TcpConnection(const InetAddress &inetAddress) {
    m_socket = std::make_unique<Socket>(inetAddress, SOCK_TYPE::TCP);
}

void TcpConnection::recv(std::string &msg) {
    char buf[1024];
    while(m_socket->read(buf, 1024) > 0) {
        msg+=buf;
    }
}