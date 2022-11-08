//
// Created by egor on 11/3/22.
//

#include "Dispatcher.hpp"
#include "SocketReader.hpp"
#include "Generator.hpp"
#include <iostream>

Dispatcher::Dispatcher(TcpConnectionPtr const& connection): m_connection(connection) {
}

void Dispatcher::setCloseConnectionCallback(CloseConnectionCallback const& closeConnectionCallback) {
    m_closeConnectionCallback = closeConnectionCallback;
}

void Dispatcher::setReceiveMessageCallback(ReceiveMessageCallback const& receiveMessageCallback) {
    m_receiveMessageCallback = receiveMessageCallback;
}

void Dispatcher::setSendMessageCallback(SendMessageCallback const& sendMessageCallback) {
    m_sendMessageCallback = sendMessageCallback;
}

Generator<int> Dispatcher::pollEvents() {
    SocketReader socketReader;
    while(m_connection->isConnected()) {
        auto result = socketReader.read(m_connection->fd());
        switch (result) {
            case READ_STATUS::GOT_MESSAGE: {
                m_receiveMessageCallback(m_connection, &socketReader);
                break;
            }
            case READ_STATUS::CONNECTION_CLOSED: {
                m_closeConnectionCallback(m_connection);
                break;
            }
            default:
                std::cout << "Unexpected status: ";
        }
        co_yield static_cast<int>(result);
    }
}

Generator<int>& Dispatcher::getGenerator() {
    if(!m_generator) {
        m_generator = std::make_unique<Generator<int>>(pollEvents());
    }
    return *m_generator;
}

bool Dispatcher::operator<(Dispatcher const& r) {
    return m_connection < r.m_connection;
}

const TcpConnectionPtr &Dispatcher::getConnectionPtr() const {
    return m_connection;
}