//
// Created by egor on 11/14/22.
//

#include "HttpParser.hpp"
#include "StringsFunctions.hpp"

HttpParserBuilder::HttpParserBuilder(std::string_view message): m_message(message) {
    std::string accumulator;
    for(int i = 0; i < m_message.size() - 1; ++i) {
        accumulator += m_message[i];
        if(isDelimiter(m_message[i+1])) {
            if (getMethodFromName(accumulator) != MESSAGE_METHOD::UNDEFINED) {
                m_method = getMethodFromName(accumulator);
                break;
            }
            else {
                m_method = MESSAGE_METHOD::UNDEFINED;
                break;
            }
        }
    }
}


MESSAGE_TYPE HttpParserBuilder::getMessageType() const {
    MESSAGE_METHOD messageMethod = getMessageMethod();
    if(messageMethod == MESSAGE_METHOD::UNDEFINED)
        return MESSAGE_TYPE::RESPONSE;
    return MESSAGE_TYPE::REQUEST;
}

std::string HttpParserBuilder::getMessage() const {
    return m_message;
}

MESSAGE_METHOD HttpParserBuilder::getMessageMethod() const {
    return m_method;
}

MESSAGE_METHOD HttpParserBuilder::getMethodFromName(std::string_view message) {
    switch (const_hash(message.data())) {
        case const_hash("GET"): return MESSAGE_METHOD::GET;
        case const_hash("HEAD"): return MESSAGE_METHOD::HEAD;
        case const_hash("POST"): return MESSAGE_METHOD::POST;
        case const_hash("PUT"): return MESSAGE_METHOD::PUT;
        case const_hash("DELETE"): return MESSAGE_METHOD::DELETE;
        case const_hash("CONNECT"): return MESSAGE_METHOD::CONNECT;
        case const_hash("OPTIONS"): return MESSAGE_METHOD::OPTIONS;
        default: return MESSAGE_METHOD::UNDEFINED;
    }
}