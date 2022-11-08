//
// Created by egor on 11/3/22.
//

#pragma once

#include "TcpConnection.hpp"
#include "callbacks.hpp"

template<typename T>
class Generator;

class Dispatcher {
public:
    Dispatcher(TcpConnectionPtr const&);
public:
    void setReceiveMessageCallback(ReceiveMessageCallback const&);
    void setCloseConnectionCallback(CloseConnectionCallback const&);
    void setSendMessageCallback(SendMessageCallback const&);

public:
    Generator<int>& getGenerator();
    TcpConnectionPtr const& getConnectionPtr() const;
    bool operator<(Dispatcher const& r);

private:
    Generator<int> pollEvents();

private:
    SendMessageCallback m_sendMessageCallback;
    ReceiveMessageCallback m_receiveMessageCallback;
    CloseConnectionCallback m_closeConnectionCallback;

    std::unique_ptr<Generator<int>> m_generator;
    TcpConnectionPtr const& m_connection;
};