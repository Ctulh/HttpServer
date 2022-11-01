//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "TcpConnection.hpp"
#include "ConnectionAcceptor.hpp"

#include <iostream>
#include <atomic>
#include <functional>
#include <thread>

class TcpServer {
public:
    TcpServer(const InetAddress& inet, std::function<std::string(std::string const&)> const& callback):
                                  m_inetAddress(inet), m_callback(callback) {
        m_connectionAcceptor = std::make_unique<ConnectionAcceptor>(m_inetAddress);
        m_connectionAcceptor->setReceiveConnectionCallback(std::bind(&TcpServer::acceptConnectionCallback, this, std::placeholders::_1));
    }

    void run() {
        m_isRunning.test_and_set();

        std::thread t1 ([this](){m_connectionAcceptor->run();});
        t1.detach();

        while(m_isRunning.test()) {
            if(m_connection) {
                char buf[1024];
                auto result = ::recv(m_connection->fd(), buf, 1024,0);
                if (result > 0) {
                    receiveMessageCallback({buf, 1024}); // todo move from tcpServer to PollDispatcher or something
                }
            }
        }
    }

    void stop() {
        m_isRunning.clear();
        m_connectionAcceptor->stop();
    }
private:
    void acceptConnectionCallback(int fd) { //TODO close connection callback
        m_connection = std::make_unique<TcpConnection>(fd);
        if(m_connection) {
            std::cout << "Got new connection: " << fd << '\n';
        }
    }
    void receiveMessageCallback(std::string const& message) {
        if(m_connection)
            m_connection->send(message.c_str(), message.size());
    }


private:
    std::atomic_flag m_isRunning;
    std::unique_ptr<ConnectionAcceptor> m_connectionAcceptor;
    std::unique_ptr<TcpConnection> m_connection;
    InetAddress m_inetAddress;
    std::function<std::string(std::string const&)> m_callback;
};