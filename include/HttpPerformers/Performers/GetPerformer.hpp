//
// Created by egor on 11/14/22.
//

#pragma once

#include "IPerformer.hpp"
#include "HttpParser/HttpRequest.hpp"

class GetPerformer: public IPerformer {
public:
    GetPerformer(HttpRequest const& request, std::string_view projectPath);
public:
    std::string getResponse() override;

private:
    std::string m_projectPath;
    HttpRequest m_httpRequest;
};