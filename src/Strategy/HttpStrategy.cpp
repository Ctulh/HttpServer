//
// Created by egor on 11/14/22.
//

#include "HttpStrategy.hpp"
#include <iostream>

using namespace boost::beast;

void HttpStrategy::onReceiveMessage(const TcpConnectionPtr &connection, SocketReaderPtr socketReader) {
    auto request = socketReader->getBuffer();
}


