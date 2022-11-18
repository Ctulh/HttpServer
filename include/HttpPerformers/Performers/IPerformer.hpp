//
// Created by egor on 11/14/22.
//

#pragma once

#include <string>

class IPerformer {
public:
    virtual ~IPerformer() = default;

public:
    virtual std::string getResponse() = 0;
};
