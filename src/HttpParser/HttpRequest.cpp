//
// Created by egor on 11/15/22.
//
#include "HttpRequest.hpp"
#include "StringsFunctions.hpp"
#include <regex>
#include <iostream>

std::string HttpRequest::getPath() {
    if(m_path.empty()) {
        std::string pathAccumulator;
        for(int i = 0; i < m_message.size(); ++i) {
            if(m_message[i] == '/') {
                pathAccumulator += m_message[i];
                int j = 1;
                while(!isDelimiter(m_message[i + j])) {
                    pathAccumulator += m_message[i+j];
                    j++;
                }
                if(isPath(pathAccumulator)) {
                    m_path = pathAccumulator;
                    return m_path;
                }
                std::cout << "Path: " << m_message << " doesnt fit path regex \n";
            }
        }
    }
    return m_path;
}

MESSAGE_METHOD HttpRequest::getMethod() const {
    return m_method;
}

bool HttpRequest::isPath(std::string path) const {
    std::regex pathRegex("^(/[^/ ]*)+/?$");
    return std::regex_match(path, pathRegex);
}

std::string HttpRequest::getHost() {
    if(m_host.empty()) {
        std::string hostString = "Host:";
        auto it = m_message.find(hostString);

        if(it == std::string::npos) {
            std::cout << "Host not found \n";
            return "";
        }

        it += hostString.size();
        std::size_t hostEndIndex = 0;

        for(auto i = it; i < m_message.size(); i++) {
            auto symbol = m_message[i];
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

        m_host = m_message.substr(hostBeginIndex, length);
        return m_host;
    }
    return m_host;
}

bool HttpRequest::isKeepAlive() const {
    if(m_message.empty())
        return false;

    std::string keepAliveFieldString = "Connection:";
    auto it = m_message.find(keepAliveFieldString);

    if(it == std::string::npos)
        return false;

    auto begin = it + keepAliveFieldString.size() + 1; // because of empty space
    auto end = m_message.substr(begin, m_message.size()).find('\n');

    auto keepAliveString = m_message.substr(begin, end);

    if(keepAliveString == "keep-alive")
        return true;
    return false;
}
