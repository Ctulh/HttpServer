//
// Created by egor on 11/14/22.
//

#pragma once

#include <string_view>
#include <memory>

#include "MessageMethods.hpp"

class HttpParser {
public:
    HttpParser(std::string_view message);

public:
    MESSAGE_METHOD getMessageMethod();

private:
    MESSAGE_METHOD getMethodFromName(std::string_view message);

private:
    std::string m_message;
    bool m_isRequest;
};