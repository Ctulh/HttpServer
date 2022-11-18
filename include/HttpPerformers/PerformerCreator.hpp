//
// Created by egor on 11/14/22.
//

#pragma once

#include <memory>
#include <optional>

#include "HttpParser/HttpRequest.hpp"
#include "Performers//IPerformer.hpp"

class PerformerCreator {
public:
    static std::unique_ptr<IPerformer> getMethod(HttpRequest const&, std::string_view path);
};
