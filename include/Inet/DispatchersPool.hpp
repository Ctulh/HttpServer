//
// Created by egor on 11/8/22.
//

#pragma once

#include "Dispatcher.hpp"
#include "TcpConnection.hpp"

#include <set>

using DispatcherPtr = std::unique_ptr<Dispatcher>;

class DispatchersPool {
public:
    ~DispatchersPool();
public:
    void add(TcpConnectionPtr const&, std::unique_ptr<Dispatcher> dispatcher);
    void remove(TcpConnectionPtr const&);
    void poll();
private:
    std::set<DispatcherPtr> m_dispatchers;
};
