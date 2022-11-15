set(LIB_NAME StringsMethodsLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Utils/StringsFunctions)

set(HEADERS ${INCLUDE_DIR}/StringsFunctions.hpp)
set(SOURCES StringsFunctions.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR})