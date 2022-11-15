set(LIB_NAME HttpParserLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/HttpParser)

set(STRINGS_METHODS StringsMethodsLib)

set(HEADERS ${INCLUDE_PATH}/HttpParser.hpp)

set(SOURCES HttpParser.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH})

target_link_libraries(${LIB_NAME} PRIVATE ${STRINGS_METHODS})
