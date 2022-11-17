//
// Created by egor on 11/8/22.
//

#include "DispatchersPool.hpp"
#include "SocketReader.hpp"
#include "Generator.hpp"



void DispatchersPool::add(TcpConnectionPtr const& connection, std::unique_ptr<Dispatcher> dispatcher) {
    m_dispatchers.insert(std::move(dispatcher));
}

void DispatchersPool::remove(TcpConnectionPtr const& connection) {
    auto it = std::find_if(m_dispatchers.begin(), m_dispatchers.end(), [&connection](auto&& el){
        return el->getConnectionPtr() == connection;
    });
    if(it != m_dispatchers.end())
        m_iterator = m_dispatchers.erase(it);

}

void DispatchersPool::poll() {
    if(m_dispatchers.empty())
        return;
    for(m_iterator = m_dispatchers.begin(); m_iterator != m_dispatchers.end(); m_iterator++) {
        auto result =  m_iterator->get()->poll();
        if(result == READ_STATUS::CONNECTION_CLOSED) {
            if(m_dispatchers.empty())
                break;
        }
    }

}


DispatchersPool::~DispatchersPool() = default;
