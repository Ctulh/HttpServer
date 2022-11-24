//
// Created by egor on 11/14/22.
//

#pragma once

#include "IPerformer.hpp"
#include "HttpParser/HttpRequestParser.hpp"

class GetPerformer: public IPerformer {
public:
    GetPerformer(HttpRequestParser const& request, std::string_view projectPath);
public:
    std::string getResponse() override;

private:
    std::string m_projectPath;
    HttpRequestParser m_httpRequest;
};