//
// Created by egor on 11/15/22.
//
#include "HttpRequestParser.hpp"
#include "StringsFunctions.hpp"
#include <regex>
#include <iostream>
#include <ranges>
#include <algorithm>


HttpRequestParser::HttpRequestParser(std::string_view message, MESSAGE_METHOD method) {
    m_request.message = message;
    m_request.method = method;
    parse();
}
HttpRequestParser::HttpRequestParser(HttpRequestParser const& request) {
    m_request = request.m_request;
    parse();
}

void HttpRequestParser::parse() {
    m_request.path = pathParse();
    m_request.host = hostParse();
    m_request.connection = connectionParse();
   // m_request.version = httpVersionParse();
  //  m_request.body = bodyParse();
}

std::string HttpRequestParser::pathParse() {
    std::string pathAccumulator;
    std::string& message = m_request.message;

    for(int i = 0; i < message.size(); ++i) {
        if(message[i] == '/') {
            pathAccumulator += message[i];
            int j = 1;
            while(!isDelimiter(message[i + j])) {
                pathAccumulator += message[i+j];
                j++;
            }
            if(isPath(pathAccumulator)) {
                return pathAccumulator;
            }
            std::cout << "Path: " << message << " doesnt fit path regex \n";
        }
    }
    return  "";
}

std::string HttpRequestParser::hostParse() {
    std::string hostString = "Host:";
    std::string& message = m_request.message;

    auto it = message.find(hostString);

    if(it == std::string::npos) {
        std::cout << "Host not found \n";
        return "";
    }

    it += hostString.size();
    std::size_t hostEndIndex = 0;

    for(auto i = it; i < message.size(); i++) {
        auto symbol = message[i];
        if(symbol == '\n') {
            hostEndIndex = i;
            break;
        }
    }

    if(hostEndIndex == 0) {
        std::cout << "End of the host not found \n";
        return "";
    }

    auto hostBeginIndex = it + 1; // Because of space at begin
    auto length = hostEndIndex - hostBeginIndex;

    return message.substr(hostBeginIndex, length);
}

std::string HttpRequestParser::connectionParse() {
    std::string& message = m_request.message;

    if(message.empty())
        return "";

    std::string keepAliveFieldString = "Connection:";
    auto it = message.find(keepAliveFieldString);

    if(it == std::string::npos)
        return "";

    auto begin = it + keepAliveFieldString.size() + 1; // because of empty space before connection string
    auto end = message.substr(begin, message.size()).find('\n');

    auto connectionString = message.substr(begin, end);

    return connectionString;
}

std::string HttpRequestParser::getPath() const {
    return m_request.path;
}

MESSAGE_METHOD HttpRequestParser::getMethod() const {
    return m_request.method;
}

std::string HttpRequestParser::getHost() const {
    return m_request.host;
}

std::string HttpRequestParser::getConnection() const {
    return m_request.connection;
}

bool HttpRequestParser::isPath(std::string path) const {
    std::regex pathRegex("^(/[^/ ]*)+/?$");
    return std::regex_match(path, pathRegex);
}



bool HttpRequestParser::isKeepAlive() const {
    return (m_request.connection == "Keep-alive") || (m_request.connection == "keep-alive");
}
