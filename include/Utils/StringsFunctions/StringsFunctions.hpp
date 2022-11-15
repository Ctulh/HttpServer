//
// Created by egor on 11/15/22.
//

#pragma once

bool isDelimiter(char symbol);
unsigned constexpr const_hash(char const *input);


constexpr unsigned int const_hash(const char *input) {
    return *input ?
           static_cast<unsigned int>(*input) + 33 * const_hash(input + 1) :
           5381;
}