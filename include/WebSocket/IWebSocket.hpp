//
// Created by egor on 10/13/22.
//

#pragma once

class IWebSocket {
public:
    virtual void handleMessage() = 0;
    virtual void handleCloseConnection() = 0;
    virtual void handleNewConnection() = 0;
public:
    ~IWebSocket() = default;
};