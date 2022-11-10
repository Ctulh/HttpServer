//
// Created by egor on 10/25/22.
//

#pragma once

#include <functional>
#include <memory>

class TcpConnection;
class SocketReader;

using TcpConnectionPtr = std::unique_ptr<TcpConnection>;
using SocketReaderPtr = std::shared_ptr<SocketReader>;

using ReceiveMessageCallback = std::function<void(TcpConnectionPtr const&, SocketReaderPtr const)>;
using SendMessageCallback = std::function<void(TcpConnectionPtr const&)>;
using ReceiveConnectionCallback = std::function<void(int)>;
using CloseConnectionCallback = std::function<void(TcpConnectionPtr const&)>;
