//
// Created by ctuh on 11/24/22.
//

#pragma once

#include <string>

#include "HttpVersion.hpp"

struct HttpResponse {
    HttpResponse() = default;
    HttpResponse(HttpResponse const&) = default;
public:
    HttpVersion version;
    int statusCode;
    std::string dateTime;
    std::string server;
    std::string contentType;
    std::string connection;
    std::string body;
    std::string lastModified;
};
