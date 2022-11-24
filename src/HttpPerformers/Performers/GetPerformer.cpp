//
// Created by egor on 11/14/22.
//

#include "Performers/GetPerformer.hpp"
#include "HttpParser/HttpResponseBuilder.hpp"

#include <filesystem>
#include <fstream>
#include <map>

GetPerformer::GetPerformer(const HttpRequestParser &request, std::string_view projectPath): m_httpRequest(request),
                                                                                            m_projectPath(projectPath) {}

std::string GetPerformer::getResponse() {
    std::string filepath;
    HttpResponseBuilder responseBuilder;

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

    responseBuilder.setHttpVersion({1,1}); // TODO
    responseBuilder.setStatusCode(200);
    responseBuilder.setCurrentDateTime();
    responseBuilder.setServer("OwnHttpServer");

    responseBuilder.setLastModifiedDateTime("Wed, 22 Jul 2009 19:15:56 GMT");
    responseBuilder.setContentTypeFromFilename(filepath);
    responseBuilder.setConnectionStatus("close");
    responseBuilder.setBody(resultString);

    return responseBuilder.getResult();
}
