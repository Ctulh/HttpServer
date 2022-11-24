//
// Created by ctuh on 11/24/22.
//

#include <iostream>
#include <sstream>
#include <iomanip>

#include "HttpResponseBuilder.hpp"

HttpResponseBuilder::HttpResponseBuilder(): m_fileExtensionContentType({
                                                                           {".html", "text/html"},
                                                                           {".css", "text/css"}
                                                                          }) // TODO load from config
{
    m_statusCodeDescription.insert({200, "OK"});
}

void HttpResponseBuilder::setHttpVersion(HttpVersion httpVersion) {
    m_httpResponse.version = httpVersion;
}

void HttpResponseBuilder::setStatusCode(int statusCode) {
    m_httpResponse.statusCode = statusCode;
}

void HttpResponseBuilder::setDateTime(std::string_view dateTime) {
    m_httpResponse.dateTime = dateTime;
}

void HttpResponseBuilder::setCurrentDateTime() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    m_httpResponse.dateTime = oss.str();
}

void HttpResponseBuilder::setLastModifiedDateTime(std::string_view lastModifiedDateTime) {
    m_httpResponse.lastModified = lastModifiedDateTime;
}

void HttpResponseBuilder::setServer(std::string_view server) {
    m_httpResponse.server = server;
}

void HttpResponseBuilder::setContentType(std::string_view contentType) {
    m_httpResponse.contentType = contentType;
}

void HttpResponseBuilder::setContentTypeFromFilename(std::string_view filename) {
    auto it =  filename.find_last_of('.');
    std::string fileExtension (filename.substr(it, filename.size()));

    if(auto contentType = m_fileExtensionContentType[fileExtension];
       !contentType.empty()) {
        m_httpResponse.contentType = contentType;
    } else {
        std::cout << "Cannot find contentType for " << filename << '\n';
    }
}

void HttpResponseBuilder::setConnectionStatus(std::string_view connectionStatus) {
    m_httpResponse.connection = connectionStatus;
}

void HttpResponseBuilder::setBody(std::string_view body) {
    m_httpResponse.body = body;
}

std::string HttpResponseBuilder::getResult() const {
    std::stringstream resultString;

    if(m_httpResponse.version.major != 0 && m_httpResponse.version.minor != 0)
        resultString << "HTTP/" << std::to_string(m_httpResponse.version.major) << '.' << std::to_string(m_httpResponse.version.minor) << ' ';
    if(m_httpResponse.statusCode != 0)
        resultString << std::to_string(m_httpResponse.statusCode) << ' ' << m_statusCodeDescription.at(m_httpResponse.statusCode) << '\n';
    if(!m_httpResponse.dateTime.empty())
        resultString << "Date: " << m_httpResponse.dateTime << '\n';
    if(!m_httpResponse.server.empty())
        resultString << "Server: " << m_httpResponse.server << '\n';
    if(!m_httpResponse.lastModified.empty())
        resultString << "Last-Modified: " << m_httpResponse.lastModified << '\n';

    resultString << "Content-Length: " << std::to_string(m_httpResponse.body.size()) << '\n';

    if(!m_httpResponse.contentType.empty())
        resultString << "Content-Type: " << m_httpResponse.contentType << '\n';
    if(!m_httpResponse.connection.empty())
        resultString << m_httpResponse.connection << "\r\n\r\n";

    resultString << m_httpResponse.body;

    return resultString.str();
}