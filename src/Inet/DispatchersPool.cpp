//
// Created by egor on 11/8/22.
//

#include "DispatchersPool.hpp"

#include "Generator.hpp"



void DispatchersPool::add(TcpConnectionPtr const& connection, Dispatcher&& dispatcher) {
    m_dispatchers.insert(std::unique_ptr<Dispatcher>(&dispatcher));
}

void DispatchersPool::remove(TcpConnectionPtr const& connection) {
    auto it = std::find_if(m_dispatchers.begin(), m_dispatchers.end(), [&connection](auto&& el){
        return el->getConnectionPtr() == connection;
    });
    if(it != m_dispatchers.end())
        m_dispatchers.erase(it);
}

void DispatchersPool::poll() {
    for(auto&& dispatcher: m_dispatchers) {
        auto& generator = dispatcher->getGenerator();
        generator.next();
        auto result = generator.getValue();
    }
}


DispatchersPool::~DispatchersPool() = default;
