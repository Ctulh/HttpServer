//
// Created by egor on 11/2/22.
//

#include "SocketReader.hpp"

#include <future>
#include <sys/socket.h>
#include <iostream>

namespace {
    constexpr int BUFFER_SIZE = 1024;
}

READ_STATUS SocketReader::read(int fd) {
    int result;
    for(;;) {
        char buf[BUFFER_SIZE];
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); //TODO fix
        result = ::recv(fd, buf, BUFFER_SIZE, 0);
        if(result == BUFFER_SIZE) {
            m_buffer += buf;
            continue;
        }
        else if(result == 0)
            break;
        else if(result == -1) {
            return ::CONNECTION_CLOSED;
        }
        else if(result < BUFFER_SIZE) {
            m_buffer += buf;
            break;
        }
    }

    std::cout << result << '\n';

    if(!m_buffer.empty())
        return ::GOT_MESSAGE;
    return ::EMPTY_MESSAGE;
}

std::string SocketReader::getBuffer() {
    return m_buffer;
}

void SocketReader::clear() {
    m_buffer.clear();
}