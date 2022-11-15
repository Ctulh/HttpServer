set(LIB_NAME HttpParserLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/HttpParser)

set(STRINGS_METHODS StringsMethodsLib)

set(HEADERS ${INCLUDE_PATH}/HttpParser.hpp
            ${INCLUDE_PATH}/HttpRequest.hpp
            ${INCLUDE_PATH}/HttpResponse.hpp
            ${INCLUDE_PATH}/MessageMethods.hpp)

set(SOURCES HttpParser.cpp
            HttpRequest.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH})

target_link_libraries(${LIB_NAME} PRIVATE ${STRINGS_METHODS})
