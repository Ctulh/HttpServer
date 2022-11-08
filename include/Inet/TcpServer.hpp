//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "TcpConnection.hpp"
#include "ConnectionAcceptor.hpp"
#include "SocketReader.hpp"
#include "Dispatcher.hpp"
#include "Generator.hpp"
#include "callbacks.hpp"

#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <set>

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

            if(m_dispatcher) {
                auto generator = m_dispatcher->pollEvents();
                generator.next();
                generator.getValue();
            }

            //TODO callback after range based loop for remove SIGSEGv
        }
    }

    void stop() {
        m_isRunning.clear();
        m_connectionAcceptor->stop();
    }
private:
    void connectionClosed(TcpConnectionPtr const& connection) {
        std::cout << "Close connection: " << connection->fd() << '\n';
        connection->shutdown();
        m_connections.erase(connection);
    }
    void acceptConnectionCallback(int fd) { //TODO close connection callback
        auto newConnection = std::make_unique<TcpConnection>(fd);
        if(newConnection) {
            std::cout << "Got new connection: " << fd << '\n';
        }
        m_connections.insert(std::move(newConnection));
        m_dispatcher = std::make_unique<Dispatcher>(*m_connections.begin());
        m_dispatcher->setReceiveMessageCallback(std::bind(&TcpServer::receiveMessageCallback, this, std::placeholders::_1, std::placeholders::_2));
        m_dispatcher->setCloseConnectionCallback(std::bind(&TcpServer::connectionClosed, this, std::placeholders::_1));
        m_pollers.push_back(std::move(m_dispatcher->pollEvents()));
    }
    void receiveMessageCallback(TcpConnectionPtr const& connection, SocketReader* socketReader) {
        //connection->send(message.c_str(), message.size());
        auto message = socketReader->getBuffer();
        connection->send(message.c_str(), message.size());
        socketReader->clear();
    }

private:
    std::atomic_flag m_isRunning;
    std::unique_ptr<ConnectionAcceptor> m_connectionAcceptor;
    std::set<TcpConnectionPtr> m_connections;
    std::vector<Generator<int>> m_pollers;
    std::unique_ptr<Dispatcher> m_dispatcher;
    InetAddress m_inetAddress;
    std::function<std::string(std::string const&)> m_callback;
};