set(LIB_NAME StrategyLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/Strategy)


set(HEADERS ${INCLUDE_PATH}/EchoStrategy.hpp
            ${INCLUDE_PATH/HttpStrategy.hpp})
set(SOURCES EchoStrategy.cpp
            HttpStrategy.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH}
                                              ${PROJECT_SOURCE_DIR}/include/Inet
                                              ${PROJECT_SOURCE_DIR}/include/
                                              ${CONAN_INCLUDE_DIRS_BOOST}
                                                )

target_link_libraries(${LIB_NAME} PRIVATE HttpPerformersLib InetLib)