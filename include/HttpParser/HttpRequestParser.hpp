//
// Created by egor on 11/15/22.
//

#pragma once

#include <string>

#include "MessageMethods.hpp"
#include "HttpRequest.hpp"
#include "HttpVersion.hpp"


class HttpRequestParser {
public:
    HttpRequestParser(std::string_view message, MESSAGE_METHOD method);
    HttpRequestParser(HttpRequestParser const& request);
public:
    MESSAGE_METHOD getMethod() const;
    std::string getPath() const;
    std::string getHost() const;
    std::string getConnection() const;
    bool isKeepAlive() const;
    HttpVersion getHttpVersion();
private:
    void parse();
    std::string pathParse();
    std::string hostParse();
    std::string connectionParse();

    bool isPath(std::string path) const;
private:
    HttpRequest m_request;
};