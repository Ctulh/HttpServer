set(LIB_NAME HttpPerformersLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/HttpPerformers)

set(HEADERS ${INCLUDE_PATH}/PerformerCreator.hpp)

set(SOURCES PerformerCreator.cpp
            Performers/GetPerformer.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH}
                                              ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} PRIVATE HttpParserLib)
