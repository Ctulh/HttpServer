//
// Created by ctuh on 11/24/22.
//

#pragma once

#include <string>

#include "MessageMethods.hpp"

struct HttpVersion {
    int major;
    int minor;
};

struct HttpRequest {
public:
    HttpRequest() = default;
    HttpRequest(HttpRequest const&) = default;

public:
    std::string connection;
    MESSAGE_METHOD method;
    HttpVersion version;
    std::string message;
    std::string path;
    std::string body;
    std::string host;
};
