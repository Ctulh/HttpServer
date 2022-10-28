//
// Created by egor on 10/28/22.
//

#include "ConnectionAcceptor.hpp"

ConnectionAcceptor::ConnectionAcceptor(InetAddress const& inetAddress) {
    m_socket = std::make_unique<Socket>(inetAddress, SOCK_TYPE::TCP);
    m_socket->bind();

    m_isRunning.test_and_set();
}

void ConnectionAcceptor::setReceiveConnectionCallback(ReceiveConnectionCallback const& callback) {
    m_receiveConnectionCallback = callback;
}

void ConnectionAcceptor::run() {
    m_socket->listen();

    while(m_isRunning.test()) {
        int newConnectionFd = m_socket->accept();
        if(newConnectionFd != -1) {
            m_receiveConnectionCallback(newConnectionFd);
        }
    }
}

void ConnectionAcceptor::stop() {
    m_isRunning.clear();
}