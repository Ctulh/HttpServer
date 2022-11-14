//
// Created by egor on 11/14/22.
//

#pragma once

#include "TcpConnection.hpp"
#include "SocketReader.hpp"

enum REQUEST_TYPE {
    GET = 1
};

class HttpStrategy {
public:
    void onReceiveMessage(TcpConnectionPtr const& connection, SocketReaderPtr socketReader);
private:
    REQUEST_TYPE getRequestType(std::string const& request) const;
    std::string getRequest(std::string const& request) const;
};