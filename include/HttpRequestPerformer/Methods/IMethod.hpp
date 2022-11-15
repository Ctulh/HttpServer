//
// Created by egor on 11/14/22.
//

#pragma once

#include <string>

class IMethod {
public:
    virtual ~IMethod() = default;

public:
    virtual std::string getResponse() = 0;
};
