//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "TcpConnection.hpp"
#include "ConnectionAcceptor.hpp"
#include "SocketReader.hpp"
#include "DispatchersPool.hpp"
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
        m_dispatcherPool = std::make_unique<DispatchersPool>();
    }

    void run() {
        m_isRunning.test_and_set();

        std::thread t1 ([this](){m_connectionAcceptor->run();});
        t1.detach();

        while(m_isRunning.test()) {
            if(m_connections.empty())
                continue;

            m_dispatcherPool->poll();

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
        m_dispatcherPool->remove(connection);
    }
    void acceptConnectionCallback(int fd) { //TODO close connection callback
        auto newConnection = std::make_unique<TcpConnection>(fd);
        if(newConnection) {
            std::cout << "Got new connection: " << fd << '\n';
        }

        auto insertPos = m_connections.insert(m_connections.end(), std::move(newConnection));

        auto dispatcher = Dispatcher(*insertPos);
        dispatcher.setReceiveMessageCallback([this](TcpConnectionPtr const& connection, SocketReader* socketReader) {
            this->receiveMessageCallback(connection, socketReader);
        });
        dispatcher.setCloseConnectionCallback([this](TcpConnectionPtr const& connection) {
            this->connectionClosed(connection);
        });

        m_dispatcherPool->add(*insertPos, std::move(dispatcher));
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
    std::unique_ptr<DispatchersPool> m_dispatcherPool;
    std::set<TcpConnectionPtr> m_connections;
    InetAddress m_inetAddress;
    std::function<std::string(std::string const&)> m_callback;
};