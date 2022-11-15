//
// Created by egor on 11/14/22.
//

#pragma once

#include "IMethod.hpp"

class GetMethod: public IMethod {
public:
    GetMethod(std::string_view request);
public:
    std::string getResponse() override;

private:
    std::string m_requestString;
};