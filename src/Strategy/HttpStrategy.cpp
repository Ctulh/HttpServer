//
// Created by egor on 11/14/22.
//

#include "HttpStrategy.hpp"
#include "HttpParser/HttpParser.hpp"
#include "HttpParser/HttpRequest.hpp"
#include "HttpParser/MessageMethods.hpp"
#include "HttpParser/HttpGetPerformer.hpp"

#include <iostream>

void HttpStrategy::onReceiveMessage(const TcpConnectionPtr &connection, SocketReaderPtr socketReader) {
    HttpParser httpParser(socketReader->getBuffer());
    std::cout << socketReader->getBuffer();
    if(httpParser.getMessageMethod() == GET) {
        HttpGetPerformer httpGetPerformer(HttpRequest(socketReader->getBuffer(), GET));
        auto response = httpGetPerformer.getResponse();
        connection->send(response.c_str(), response.size());
        m_closeCallback(connection);
    }
}

void HttpStrategy::setCloseConnection(CloseConnectionCallback callback) {
    m_closeCallback = callback;
}


