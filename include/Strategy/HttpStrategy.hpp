//
// Created by egor on 11/14/22.
//

#pragma once

#include "TcpConnection.hpp"
#include "SocketReader.hpp"
#include "Inet/callbacks.hpp"

class HttpStrategy {
public:
    HttpStrategy(std::string_view directory);
public:
    void onReceiveMessage(TcpConnectionPtr const& connection, SocketReaderPtr socketReader);
    void setCloseConnection(CloseConnectionCallback);
private:
    CloseConnectionCallback m_closeCallback;
    std::string m_directory;
};