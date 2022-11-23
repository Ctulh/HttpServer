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
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::GET);
    ASSERT_EQ(httpParser.getMessage(), message);
}

TEST(HttpParser, HeadMethodTest) {
    constexpr char const *message = "HEAD /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::HEAD);
}

TEST(HttpParser, PostMethodTest) {
    constexpr char const *message = "POST /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::POST);
}

TEST(HttpParser, PutMethodTest) {
    constexpr char const *message = "PUT /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::PUT);
}

TEST(HttpParser, DeleteMethodTest) {
    constexpr char const *message = "DELETE /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::DELETE);
}

TEST(HttpParser, ConnectMethodTest) {
    constexpr char const *message = "CONNECT /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::CONNECT);
}

TEST(HttpParser, OptionsMethodTest) {
    constexpr char const *message = "OPTIONS /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::REQUEST);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::OPTIONS);
}

TEST(HttpParser, ResponseMessageTest) {
    constexpr char const* message = "HTTP/1.1 200 OK\n"
                                    "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
                                    "Server: Apache/2.2.14 (Win32)\n"
                                    "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
                                    "Content-Length: 88\n"
                                    "Content-Type: text/html\n"
                                    "Connection: Closed";
    HttpParser httpParser(message);
    ASSERT_EQ(httpParser.getMessageType(), MESSAGE_TYPE::RESPONSE);
    ASSERT_EQ(httpParser.getMessageMethod(), MESSAGE_METHOD::UNDEFINED);
    ASSERT_EQ(httpParser.getMessage(), message);

    //HttpRequest httpRequest(message, httpParser.getMessageMethod());

    //ASSERT_EQ(httpRequest.getMethod(), MESSAGE_METHOD::UNDEFINED);
    //ASSERT_EQ(httpRequest.getPath(), "/test/test.html");
    //ASSERT_EQ(httpRequest.getHost(), "developer.mozilla.org");
    //ASSERT_TRUE(httpRequest.isKeepAlive());
}

TEST(HttpRequest, HttpRequestGetPathTest) {
    constexpr char const* message = "GET /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    HttpRequest httpRequest(message, httpParser.getMessageMethod());

    ASSERT_EQ(httpRequest.getMethod(), MESSAGE_METHOD::GET);
    ASSERT_EQ(httpRequest.getPath(), "/test/test.html");
}

TEST(HttpRequest, HttpRequestGetHostTest) {
    constexpr char const* message = "GET /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    HttpRequest httpRequest(message, httpParser.getMessageMethod());

    ASSERT_EQ(httpRequest.getHost(), "developer.mozilla.org");
}

TEST(HttpRequest, HttpRequestConnectionKeepAliveTest) {
    constexpr char const* message = "GET /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: keep-alive\n";
    HttpParser httpParser(message);
    HttpRequest httpRequest(message, httpParser.getMessageMethod());

    ASSERT_TRUE(httpRequest.isKeepAlive());
}

TEST(HttpRequest, HttpRequestConnectionCloseTest) {
    constexpr char const* message = "GET /test/test.html HTTP/1.1\n"
                                    "Host: developer.mozilla.org\n"
                                    "Accept-Language: fr\n"
                                    "Connection: Closed\n";
    HttpParser httpParser(message);
    HttpRequest httpRequest(message, httpParser.getMessageMethod());

    ASSERT_FALSE(httpRequest.isKeepAlive());
}