//
// Created by egor on 11/14/22.
//

#pragma once

#include "HttpParser.hpp"
#include "HttpRequest.hpp"
#include <gtest/gtest.h>

TEST(HttpParser, GetMethodTest) {
    constexpr char const* message = "GET /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::GET);
    ASSERT_EQ(httpParser.getMessage(), message);

    HttpRequest httpRequest(message, httpParser.getMessageMethod());

    ASSERT_EQ(httpRequest.getMethod(), MESSAGE_METHOD::GET);
    ASSERT_EQ(httpRequest.getPath(), "/test/test.html");
    ASSERT_EQ(httpRequest.getHost(), "developer.mozilla.org");
}

