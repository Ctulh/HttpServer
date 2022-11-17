//
// Created by ctuh on 11/17/22.
//

#ifndef HTTPSERVER_HTTPGETPERFORMER_HPP
#define HTTPSERVER_HTTPGETPERFORMER_HPP

#include "HttpRequest.hpp"
#include <filesystem>
#include <fstream>

class HttpGetPerformer {
public:
    HttpGetPerformer(HttpRequest const& httpRequest): m_request(httpRequest) {}
    std::string getResponse() {
        auto filepath = "/home/ctuh/Desktop/web/index.html";
        if(!std::filesystem::exists(filepath)) {
            return "";
        }

        std::fstream file(filepath, std::fstream::in);
        std::string resultString((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        std::string returnString;
        returnString = "HTTP/1.1 200 OK\n"
                       "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
                       "Server: Apache/2.2.14 (Win32)\n"
                       "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
                       "Content-Length: " + std::to_string(resultString.size()) + "\n"
                       "Content-Type: text/html\n"
                       "Connection: Closed \r\n\r\n" + resultString;
        return returnString;
    }
private:
    HttpRequest m_request;
};

#endif //HTTPSERVER_HTTPGETPERFORMER_HPP
