set(TARGET_NAME tests)

set(HTTP_PARSER_PATH ${PROJECT_SOURCE_DIR}/include/HttpParser)
set(HTTP_PARSER_LIB HttpParserLib)

set(SOURCE main_test.cpp HttpParserTests.hpp)

add_executable(${TARGET_NAME} ${SOURCE})

target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS_GTEST} ${HTTP_PARSER_LIB})

target_include_directories(${TARGET_NAME} PUBLIC ${HTTP_PARSER_PATH})