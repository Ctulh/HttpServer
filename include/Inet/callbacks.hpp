//
// Created by egor on 10/25/22.
//

#pragma once

#include <functional>

class TcpConnection;

using ReceiveMessageCallback = std::function<void(TcpConnection*, char* msg, int len)>;
using ReceiveConnectionCallback = std::function<void(int)>;
