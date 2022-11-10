//
// Created by egor on 11/10/22.
//

#include "EchoStrategy.hpp"

void EchoStrategy::onReceiveMessage(TcpConnectionPtr const& connection, SocketReaderPtr const socketReader) {
    auto message = socketReader->getBuffer();
    connection->send(message.c_str(), message.size());
}