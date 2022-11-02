//
// Created by egor on 11/2/22.
//

#include "SocketReader.hpp"

#include <future>
#include <sys/socket.h>

namespace {
    constexpr int BUFFER_SIZE = 1024;
}

STATUS SocketReader::read(int fd) {
    int result;
    for(;;) {
        char buf[BUFFER_SIZE];
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
    if(!m_buffer.empty())
        return ::GOT_MESSAGE;
    if(result == 0)
        return ::CONNECTION_CLOSED;
    return ::EMPTY_MESSAGE;
}

std::string SocketReader::getBuffer() {
    return m_buffer;
}

void SocketReader::clear() {
    m_status = ::NONE;
    m_buffer.clear();
}