//
// Created by egor on 11/14/22.
//

#pragma once

#include <string_view>
#include <memory>

#include "MessageMethods.hpp"

enum MESSAGE_TYPE {
    RESPONSE = 2,
    REQUEST = 3
};


class HttpParser {
public:
    HttpParser(std::string_view message);

public:
    MESSAGE_TYPE getMessageType() const;
    MESSAGE_METHOD getMessageMethod() const;
    std::string getMessage() const;

private:
    static MESSAGE_METHOD getMethodFromName(std::string_view message) ;
    bool isPath(std::string_view message);

private:
    std::string m_message;
    MESSAGE_METHOD m_method;
};