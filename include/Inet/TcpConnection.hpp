//
// Created by egor on 10/25/22.
//

#pragma once

#include "InetAddress.hpp"
#include "callbacks.hpp"
#include "Socket.hpp"
#include <cstdio>
#include <memory>

class TcpConnection {
public:
    TcpConnection(InetAddress const& inetAddress);
    TcpConnection(int fd);
public:
    void send(const char* msg, std::size_t len);
    void recv(std::string& msg);

    void shutdown();
public:
private:
    std::unique_ptr<Socket> m_socket;
};