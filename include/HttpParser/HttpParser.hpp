//
// Created by egor on 11/14/22.
//

#pragma once

#include <string_view>
#include <memory>

#include "MessageMethods.hpp"

enum class MESSAGE_TYPE {
    RESPONSE = 1,
    REQUEST = 2,
};


class HttpParserBuilder {
public:
    HttpParserBuilder(std::string_view message);

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