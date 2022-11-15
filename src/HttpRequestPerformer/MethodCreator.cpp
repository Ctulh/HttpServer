//
// Created by egor on 11/14/22.
//

#include "MethodCreator.hpp"
#include "StringsMethods.hpp"
#include "../../include/HttpRequestPerformer/Methods/GetMethod.hpp"

std::unique_ptr<IMethod> MethodCreator::createMethod(std::string_view message) {
    auto messageType = getMessageMethod(message);
    switch (messageType) {
        case MESSAGE_METHOD::GET: return std::make_unique<GetMethod>(message);
        case MESSAGE_METHOD::POST: break;
    }
}
