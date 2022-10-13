//
// Created by egor on 10/13/22.
//

#include "Socket.hpp"
#include <string>


namespace {
    constinit int MAXRECV = 1024;
}

Socket::~Socket() {
    shutdown(m_socketFd, 2);
}

int Socket::accept() {
    int addr_length = sizeof ( m_inetAddress.getSockAddr() );
    m_acceptFd = ::accept ( m_socketFd, ( sockaddr * )m_inetAddress.getSockAddr(), ( socklen_t * ) &addr_length );

    return m_acceptFd;
}

bool Socket::listen() {
    int listen_return = ::listen(m_socketFd, SOMAXCONN);
    if (listen_return == -1) {
        return false;
    }
    return true;
}

bool Socket::bindAddress() {
    int bind_return = ::bind(m_socketFd, m_inetAddress.getSockAddr(), sizeof(sockaddr_in));
    if(bind_return == -1) {
        return false;
    }
    return true;
}

int Socket::recv(std::string& output) const {
    char buf[::MAXRECV + 1];

    int status = ::recv ( m_acceptFd, buf, MAXRECV, 0 );

    output = buf;
    return status;
}

bool Socket::send(std::string_view msg) const {
    int status = ::send ( m_socketFd, msg.data(), msg.size(), MSG_NOSIGNAL );
    if ( status == -1 ) {
        return false;
    }
    else {
        return true;
    }
}

bool Socket::connect() {
    int status;
    status = ::connect(m_socketFd, m_inetAddress.getSockAddr(), sizeof (*m_inetAddress.getSockAddr()));

    if ( status == 0 )
        return true;
    else
        return false;
}