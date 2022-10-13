//
// Created by egor on 10/13/22.
//

#pragma once

#include <string_view>

class IWebSocketConnection {
public:
    virtual void send(std::string_view msg, int len) = 0;
    virtual bool isConnected() = 0;
    virtual void shutDown() = 0;
public:
    virtual ~IWebSocketConnection() = default;
};