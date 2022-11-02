//
// Created by egor on 11/2/22.
//

#pragma once

#include <string>
#include <future>

enum STATUS {
    NONE,
    GOT_MESSAGE,
    EMPTY_MESSAGE,
    CONNECTION_CLOSED,
};

class SocketReader {
public:
    STATUS read(int fd);
    std::string getBuffer();
    void clear();
private:
    std::string m_buffer;
    STATUS m_status;
};