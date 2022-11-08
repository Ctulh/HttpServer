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
    Generator<int> pollEvents();
private:
    TcpConnectionPtr const& m_connection;
    SendMessageCallback m_sendMessageCallback;
    ReceiveMessageCallback m_receiveMessageCallback;
    CloseConnectionCallback m_closeConnectionCallback;
};