//
// Created by egor on 10/13/22.
//

#pragma once

#include "IWebSocketConnection.hpp"

class WebSocketConnectionImpl: public IWebSocketConnection {
    WebSocketConnectionImpl(std::string_view ipAddr, std::string_view port);
    void send(std::string_view msg, int len) override;
    bool isConnected() override;
    void shutDown() override;
};
