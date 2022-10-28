//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"

enum SOCK_TYPE {
    TCP = 1,
    UDP = 2
};

class Socket {
public:
    explicit Socket(const InetAddress& inetAddress, SOCK_TYPE sockType):
                                                     m_inetAddress(inetAddress)
    {
        m_socketFd = socket(AF_INET,
                            ((sockType == TCP) ? SOCK_STREAM : SOCK_DGRAM) | SOCK_NONBLOCK | SOCK_CLOEXEC,
                          0);
    }
    virtual ~Socket();

public:
    bool bind();
    bool listen();
    int accept();

    int read(char* buf, int len) const;
    int fd() const;

    bool connect();

private:
    int m_socketFd;
    InetAddress m_inetAddress;
};