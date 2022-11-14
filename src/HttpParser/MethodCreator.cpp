//
// Created by egor on 11/14/22.
//

#include "MethodCreator.hpp"

std::unique_ptr<IMethod> MethodCreator::createMethod(std::string_view message) {
    auto messageType = getMessageMethod(message);

}

MESSAGE_METHOD MethodCreator::getMessageMethod(std::string_view message) {

}