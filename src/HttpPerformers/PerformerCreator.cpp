//
// Created by egor on 11/14/22.
//

#include <iostream>
#include "PerformerCreator.hpp"

#include "Performers/GetPerformer.hpp"

std::unique_ptr<IPerformer> PerformerCreator::getMethod(HttpRequestParser const& request, std::string_view path) {
    switch (request.getMethod()) {
        case MESSAGE_METHOD::GET: return std::make_unique<GetPerformer>(request, path);
        default: std::cout << "Unexpected method \n"; break;
    }
}