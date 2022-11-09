//
// Created by egor on 10/25/22.
//

#include "TcpConnection.hpp"
#include <iostream>

TcpConnection::~TcpConnection() {
    shutdown();
}

TcpConnection::TcpConnection(int fd) {
    m_socket = std::make_unique<Socket>(fd);
    m_connected = true;
}

void TcpConnection::send(const char *msg, std::size_t len) {
    auto result = ::send(m_socket->fd(), msg, len, 0);
    std::cout << "Result: " << result << '\n';
}

TcpConnection::TcpConnection(const InetAddress &inetAddress) {
    m_socket = std::make_unique<Socket>(inetAddress, SOCK_TYPE::TCP);
}

int TcpConnection::fd() const {
    return m_socket->fd();
}

void TcpConnection::shutdown() {
    m_socket->shutDown();
}

bool TcpConnection::isConnected() const {
    return m_connected;
}