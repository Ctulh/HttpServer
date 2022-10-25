//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "Socket.hpp"

#include <iostream>
#include <atomic>
#include <functional>

class TcpServer {
public:
    TcpServer(const InetAddress& inet, std::function<std::string(std::string const&)> const& callback): m_socket(inet),
                                  m_inetAddress(inet), m_callback(callback) {
        if(!m_socket.bindAddress())
            std::cout << "ERROR BINDING" << '\n';
    }

    void run() {
        m_isRunning.test_and_set();
        if(!m_socket.listen())
            std::cout << "ERROR LISTENING" << '\n';

        std::string buf;
        std::string message;

        while(m_isRunning.test()) {
            if(!m_socket.accept())
                std::cout << "ERROR ACCEPTING" << '\n';
            while (1) {
                if(m_socket.recv(buf) <= 0) break;
                m_socket.send(m_callback(buf));
            }
        }
    }

    void stop() {
        m_isRunning.clear();
    }


private:
    std::atomic_flag m_isRunning;
    std::function<std::string(std::string const&)> m_callback;
    Socket m_socket;
    InetAddress m_inetAddress;
};