//
// Created by egor on 11/10/22.
//

#pragma once

#include "TcpConnection.hpp"
#include "SocketReader/SocketReader.hpp"

class EchoStrategy {
public:
    void onReceiveMessage(TcpConnectionPtr const& connection, SocketReaderPtr socketReader);
};
