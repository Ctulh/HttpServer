//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"


class Socket {
public:
    explicit Socket(const InetAddress& inetAddress):
                                                     m_inetAddress(inetAddress)
    {
        m_socketFd = socket(m_inetAddress.getSockAddr()->sa_family,
                          SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                          IPPROTO_TCP);
    }
    virtual ~Socket();fix

public:
    bool bindAddress();
    bool listen();
    int accept();

    bool send(std::string_view) const;
    bool connect();
    int recv(std::string&) const;

private:
    int m_acceptFd;
    int m_socketFd;
    InetAddress m_inetAddress;
};