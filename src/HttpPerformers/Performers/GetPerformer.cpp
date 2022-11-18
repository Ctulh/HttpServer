//
// Created by egor on 11/14/22.
//

#include "Performers/GetPerformer.hpp"

#include <filesystem>
#include <fstream>

GetPerformer::GetPerformer(const HttpRequest &request, std::string_view projectPath): m_httpRequest(request),
                                                                                      m_projectPath(projectPath) {}

std::string GetPerformer::getResponse() {
    std::string filepath;

    if(m_httpRequest.getPath() == "/")
        filepath = m_projectPath + "/index.html";
    else
        filepath = m_projectPath + m_httpRequest.getPath();

    if(!std::filesystem::exists(filepath)) {
        return "";
    }

    std::ifstream file(filepath);
    std::string resultString((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    file.close();

    std::string returnString;
    returnString = "HTTP/1.1 200 OK\n"
                   "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
                   "Server: Apache/2.2.14 (Win32)\n"
                   "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
                   "Content-Length: " + std::to_string(resultString.size()) + "\n"
                   "Content-Type: text/html\n"
                   "Connection: Keep-Alive \r\n\r\n" + resultString;
    return returnString;
}
