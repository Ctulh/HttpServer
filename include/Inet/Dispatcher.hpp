//
// Created by egor on 11/3/22.
//

#pragma once

#include "TcpConnection.hpp"
#include "callbacks.hpp"
#include "Generator.hpp"

class Dispatcher {
public:
    Dispatcher(TcpConnectionPtr const&);
    ~Dispatcher() {
        m_generator.reset();
    }
public:
    void setReceiveMessageCallback(ReceiveMessageCallback const&);
    void setCloseConnectionCallback(CloseConnectionCallback const&);
    void setSendMessageCallback(SendMessageCallback const&);

public:
    bool operator<(Dispatcher const& r);
    int poll();

    TcpConnectionPtr const& getConnectionPtr() const;
private:
    Generator<int>& getGenerator();
    Generator<int> pollEvents();

private:
    SendMessageCallback m_sendMessageCallback;
    ReceiveMessageCallback m_receiveMessageCallback;
    CloseConnectionCallback m_closeConnectionCallback;

    TcpConnectionPtr const& m_connection;
    std::unique_ptr<Generator<int>> m_generator;
    std::shared_ptr<SocketReader> m_socketReader;
};