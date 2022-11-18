cmake_minimum_required(VERSION 3.23)
project(HttpServer)

set(APPLICATION_NAME HttpServer)
set(HTTP_PARSER_LIB HttpParserLib)

set(CMAKE_CXX_STANDARD 20)

include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${APPLICATION_NAME} app/main.cpp)

add_subdirectory(src)

add_subdirectory(tests)


message(${CONAN_INCLUDE_DIRS_BOOST})
target_include_directories(${APPLICATION_NAME} PUBLIC ${CONAN_INCLUDE_DIRS_BOOST}
                                                      ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${APPLICATION_NAME} PRIVATE ${CONAN_LIBS_BOOST} InetLib StrategyLib ${HTTP_PARSER_LIB})
