//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"


class Socket {
public:
    explicit Socket(int sockFd): m_socketFd(sockFd) {}
    ~Socket() {
        close(m_socketFd);
    }

public:
    void bindAddress(const InetAddress& address) {
        int res = ::bind(m_socketFd, address.getSockAddr(), sizeof(sockaddr_in));
        if(res == 0) {
            return;
        } else {
            // TODO LOG
        }
    }

    void listen() {
        int res = ::listen(m_socketFd, SOMAXCONN);
        if (res < 0) {
            // TODO LOG
        }
    }

    int accept(InetAddress& addr) {
        int connectionFd;
        connectionFd = ::accept(m_socketFd, NULL, NULL);
        //TODO ERROR HANDLE
        return connectionFd;
    }

public:
    static int createTcpSocket(int family) {
        int sock = socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
        if(sock < 0) {

        }
        return sock;
    }
private:
    int m_socketFd;
};