//
// Created by egor on 10/13/22.
//

#include "Socket.hpp"
#include <string>
#include <sys/fcntl.h>

Socket::Socket(int fd) {
    m_socketFd = fd;
}

Socket::~Socket() {
    close(m_socketFd);
}

int Socket::accept() {
    socklen_t addrLength = sizeof(sockaddr_in);
    return ::accept ( m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), &addrLength);
}

int Socket::listen() {
    return ::listen(m_socketFd, SOMAXCONN);
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

    if ( status == 0 ) {
        m_isConnected = true;
        return true;
    }
    return false;
}

int Socket::fd() const {
    return m_socketFd;
}

bool Socket::isConnected() const {
    return m_isConnected;
}

void Socket::shutDown() {
    shutdown(m_socketFd, 2);
    m_isConnected = false;
}

bool Socket::setNonBlocking() const {
    int flags = fcntl(m_socketFd, F_GETFL);
    auto result = fcntl(m_socketFd, F_SETFL,flags | O_NONBLOCK);
    return (result != -1);
}
