//
// Created by egor on 11/14/22.
//

#pragma once

#include <string_view>
#include <memory>

#include "Methods/IMethod.hpp"

class HttpParser {
public:
    HttpParser(std::string_view message);
private:
    std::unique_ptr<IMethod> m_method;
};