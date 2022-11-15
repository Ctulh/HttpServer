//
// Created by egor on 11/15/22.
//

#pragma once

#include <string>

#include "MessageMethods.hpp"

struct HttpVersion {
    int major;
    int minor;
};

class HttpRequest {
public:
    HttpRequest(std::string_view message, MESSAGE_METHOD method): m_message(message), m_method(method) {}
public:
    MESSAGE_METHOD getMethod() const;
    std::string getPath();

private:
    bool isPath(std::string path) const;

private:
    HttpVersion m_version;
    std::string m_message;
    std::string m_path;
    std::string m_body;
    MESSAGE_METHOD m_method;
};