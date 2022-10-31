//
// Created by egor on 10/13/22.
//

#include "Socket.hpp"
#include <string>

Socket::~Socket() {
    shutdown(m_socketFd, 2);
}

int Socket::accept() {
    socklen_t addrLength = sizeof(sockaddr_in);
    return ::accept ( m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), &addrLength);
}

bool Socket::listen() {
    int listen_return = ::listen(m_socketFd, SOMAXCONN);
    if (listen_return == -1) {
        return false;
    }
    return true;
}

bool Socket::bind() {
    int bind_return = ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
    if(bind_return == -1) {
        return false;
    }
    return true;
}

bool Socket::connect() {
    int status;
    status = ::connect(m_socketFd, m_inetAddress->getSockAddr(), sizeof (*m_inetAddress->getSockAddr()));

    if ( status == 0 )
        return true;
    else
        return false;
}

int Socket::fd() const {
    return m_socketFd;
}

int Socket::read(char *buf, int len) const {
    return ::recv(m_socketFd, buf, len, 0);
}