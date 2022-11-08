set(LIB_NAME Coroutines)

set(LIB_PATH ${PROJECT_SOURCE_DIR}/include/Utils/Coroutines)

set(HEADERS ${LIB_PATH}/Generator.hpp)

set(SOURCES Generator.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${LIB_PATH})