//
// Created by egor on 11/14/22.
//

#include "HttpStrategy.hpp"
#include "HttpParser/HttpParser.hpp"
#include "HttpParser/HttpRequestParser.hpp"
#include "HttpPerformers/PerformerCreator.hpp"

HttpStrategy::HttpStrategy(std::string_view directory): m_directory(directory) {}

void HttpStrategy::onReceiveMessage(TcpConnectionPtr connection, SocketReaderPtr socketReader) {
    HttpParser httpParser(socketReader->getBuffer());
    auto performer = PerformerCreator::getMethod(HttpRequestParser(socketReader->getBuffer(), httpParser.getMessageMethod()), m_directory);
    std::string response = performer->getResponse();
    connection->send(response.c_str(), response.size());
    m_closeConnectionCallback(connection);
}

void HttpStrategy::setCloseConnection(CloseConnectionCallback callback) {
    m_closeConnectionCallback = callback;
}


