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