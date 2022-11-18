//
// Created by egor on 11/14/22.
//

#include "HttpStrategy.hpp"
#include "HttpParser/HttpParser.hpp"
#include "HttpParser/HttpRequest.hpp"
#include "HttpParser/MessageMethods.hpp"
#include "HttpPerformers/PerformerCreator.hpp"

#include <iostream>

HttpStrategy::HttpStrategy(std::string_view directory): m_directory(directory) {}

void HttpStrategy::onReceiveMessage(const TcpConnectionPtr &connection, SocketReaderPtr socketReader) {
    HttpParser httpParser(socketReader->getBuffer());
    std::cout << socketReader->getBuffer();
    auto performer = PerformerCreator::getMethod(HttpRequest(socketReader->getBuffer(), httpParser.getMessageMethod()), m_directory);
    auto response = performer->getResponse();
    connection->send(response.c_str(), response.size());
}

void HttpStrategy::setCloseConnection(CloseConnectionCallback callback) {
    m_closeCallback = callback;
}


