//
// Created by egor on 11/14/22.
//

#pragma once

#include <memory>

#include "Methods/IMethod.hpp"
#include "Methods/Methods.hpp"

class MethodCreator {
public:
    static std::unique_ptr<IMethod> createMethod(std::string_view message);

private:
    static MESSAGE_METHOD getMessageMethod(std::string_view message);
};