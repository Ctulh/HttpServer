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
#include "Strategy/HttpStrategy.hpp"

#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <set>
#include <utility>


class TcpServer {
public:
    TcpServer(const InetAddress& inet, HttpStrategy strategy):
                                  m_inetAddress(inet), m_strategy(std::move(strategy)) {
        m_connectionAcceptor = std::make_unique<ConnectionAcceptor>(m_inetAddress);
        m_connectionAcceptor->setReceiveConnectionCallback(std::bind(&TcpServer::acceptConnectionCallback, this, std::placeholders::_1));
        m_dispatcherPool = std::make_unique<DispatchersPool>();
        m_strategy.setCloseConnection([this](TcpConnectionPtr const& conn) {this->connectionClosed(conn);});
    }

    void run() {
        m_isRunning.test_and_set();

        std::thread t1 ([this](){m_connectionAcceptor->run();});
        t1.detach();

        while(m_isRunning.test()) {
            if(m_connections.empty())
                continue;

            if(m_isCanPoll.test())
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

        m_isCanPoll.clear();

        std::cout << "Close connection: " << connection->fd() << '\n';
        connection->shutdown();
        m_dispatcherPool->remove(connection);
        m_connections.erase(connection);

        m_isCanPoll.test_and_set();

    }
    void acceptConnectionCallback(int fd) {
        auto newConnection = std::make_unique<TcpConnection>(fd);
        if(newConnection) {
            std::cout << "Got new connection: " << fd << '\n';
        }

        m_isCanPoll.clear();

        auto insertPos = m_connections.insert(m_connections.end(), std::move(newConnection));

        auto dispatcher = std::make_unique<Dispatcher>(*insertPos);
        dispatcher->setReceiveMessageCallback([this](TcpConnectionPtr const& connection, SocketReaderPtr const socketReader) {
            this->m_strategy.onReceiveMessage(connection, socketReader);
        });
        dispatcher->setCloseConnectionCallback([this](TcpConnectionPtr const& connection) {
            this->connectionClosed(connection);
        });

        m_dispatcherPool->add(*insertPos, std::move(dispatcher));

        m_isCanPoll.test_and_set();
    }

private:
    HttpStrategy m_strategy;
    std::atomic_flag m_isRunning;
    std::atomic_flag m_isCanPoll;
    std::unique_ptr<ConnectionAcceptor> m_connectionAcceptor;
    std::unique_ptr<DispatchersPool> m_dispatcherPool;
    std::set<TcpConnectionPtr> m_connections;
    InetAddress m_inetAddress;
};