//
// Created by egor on 11/3/22.
//

#include "Dispatcher.hpp"
#include "SocketReader.hpp"
#include "Generator.hpp"
#include <iostream>

Dispatcher::Dispatcher(TcpConnectionPtr const& connection): m_connection(connection) {
    m_socketReader = std::make_shared<SocketReader>();
}

void Dispatcher::setCloseConnectionCallback(CloseConnectionCallback const& closeConnectionCallback) {
    m_closeConnectionCallback = closeConnectionCallback;
}

void Dispatcher::setReceiveMessageCallback(ReceiveMessageCallback const& receiveMessageCallback) {
    m_receiveMessageCallback = receiveMessageCallback;
}

int Dispatcher::poll() {
    if(!m_generator)
        getGenerator();
    m_generator->next();
    auto result = m_generator->getValue();
    switch (result) {
        case READ_STATUS::GOT_MESSAGE: {
            m_receiveMessageCallback(m_connection, m_socketReader);
            return READ_STATUS::GOT_MESSAGE;
        }
        case READ_STATUS::CONNECTION_CLOSED: {
            m_closeConnectionCallback(m_connection);
            return READ_STATUS::CONNECTION_CLOSED;
        }
    }
}

void Dispatcher::setSendMessageCallback(SendMessageCallback const& sendMessageCallback) {
    m_sendMessageCallback = sendMessageCallback;
}

Generator<int> Dispatcher::pollEvents() {
    while(m_connection->isConnected()) {
        auto result = m_socketReader->read(m_connection->fd());
        co_yield result;
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