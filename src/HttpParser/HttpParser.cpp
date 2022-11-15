//
// Created by egor on 11/14/22.
//

#include "HttpParser.hpp"
#include "StringsFunctions.hpp"

HttpParser::HttpParser(std::string_view message): m_message(message) {

}


MESSAGE_METHOD HttpParser::getMessageMethod() {
    std::string accumulator;
    for(int i = 0; i < m_message.size(); ++i) {
        if(isDelimiter(m_message[i])) {
            accumulator.clear();
        }

        accumulator += m_message[i];

        if(getMethodFromName(accumulator) != MESSAGE_METHOD::UNDEFINED && isDelimiter(m_message[i+1])) {
            return getMethodFromName(accumulator);
        }
    }
    return MESSAGE_METHOD::UNDEFINED;
}

MESSAGE_METHOD HttpParser::getMethodFromName(std::string_view message) {
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