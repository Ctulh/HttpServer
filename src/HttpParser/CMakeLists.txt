set(LIB_NAME HttpParserLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/HttpParser)

set(HEADERS ${INCLUDE_PATH}/HttpParser.hpp
            ${INCLUDE_PATH}/Methods/IMethod.hpp
            ${INCLUDE_PATH}/Methods/GetMethod.hpp)

set(SOURCES HttpParser.cpp
            MethodCreator.cpp
            Methods/GetMethod.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH})
