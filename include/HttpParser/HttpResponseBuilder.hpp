//
// Created by egor on 11/15/22.
//

#pragma once

#include <string_view>
#include <map>

#include "HttpVersion.hpp"
#include "HttpResponse.hpp"

class HttpResponseBuilder {
public:
    HttpResponseBuilder();

public:
    void setHttpVersion(HttpVersion httpVersion);
    void setStatusCode(int statusCode);
    void setDateTime(std::string_view dateTime);
    void setCurrentDateTime();
    void setLastModifiedDateTime(std::string_view lastModifiedDateTime);
    void setServer(std::string_view server);
    void setContentType(std::string_view contentType);
    void setContentTypeFromFilename(std::string_view filename);
    void setConnectionStatus(std::string_view connectionStatus);
    void setBody(std::string_view body);
public:
    std::string getResult() const;

private:
    HttpResponse m_httpResponse;
    std::map<std::string, std::string> m_fileExtensionContentType;
    std::map<int, std::string> m_statusCodeDescription;
};