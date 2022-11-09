//
// Created by egor on 11/2/22.
//

#pragma once

#include <string>
#include <future>

enum READ_STATUS {
    NONE,
    GOT_MESSAGE,
    EMPTY_MESSAGE,
    CONNECTION_CLOSED = -1,
};

class SocketReader {
public:
    READ_STATUS read(int fd);
    std::string getBuffer();
    void clear();
private:
    std::string m_buffer;
};