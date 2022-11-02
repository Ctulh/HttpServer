//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "TcpConnection.hpp"
#include "ConnectionAcceptor.hpp"
#include "SocketReader.hpp"

#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <set>

using ConnectionPtr = std::unique_ptr<TcpConnection>;

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
            if(m_connections.empty())
                continue;
            for(auto& connection: m_connections) {
                SocketReader socketReader;
                auto status = socketReader.read(connection->fd());
                if(status == STATUS::GOT_MESSAGE) {
                    auto message = socketReader.getBuffer();
                    receiveMessageCallback(connection, message);
                } // TODO POLLER
                else if(status == STATUS::CONNECTION_CLOSED) {
                    connectionClosed(connection);
                }
            }
            //TODO callback after range based loop for remove SIGSEGv
        }
    }

    void stop() {
        m_isRunning.clear();
        m_connectionAcceptor->stop();
    }
private:
    void connectionClosed(ConnectionPtr const& connection) {
        std::cout << "Close connection: " << connection->fd() << '\n';
        m_connections.erase(connection);
    }
    void acceptConnectionCallback(int fd) { //TODO close connection callback
        auto newConnection = std::make_unique<TcpConnection>(fd);
        if(newConnection) {
            std::cout << "Got new connection: " << fd << '\n';
        }
        m_connections.insert(std::move(newConnection));
    }
    void receiveMessageCallback(ConnectionPtr const& connection,std::string const& message) {
        connection->send(message.c_str(), message.size());
    }

private:
    std::atomic_flag m_isRunning;
    std::unique_ptr<ConnectionAcceptor> m_connectionAcceptor;
    std::set<ConnectionPtr> m_connections;
    InetAddress m_inetAddress;
    std::function<std::string(std::string const&)> m_callback;
};