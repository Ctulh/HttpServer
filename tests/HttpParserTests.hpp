//
// Created by egor on 11/14/22.
//

#pragma once

#include "HttpParser.hpp"
#include <gtest/gtest.h>

TEST(HttpParser, GetMethodTest) {
    constexpr char const* message = "GET / HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::GET);
}