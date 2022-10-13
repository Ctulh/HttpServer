set(LIB_NAME InetLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Inet)

set(HEADERS ${INCLUDE_DIR}/InetAddress.hpp
            ${INCLUDE_DIR}/Socket.hpp
            ${INCLUDE_DIR}/TcpServer.hpp)

set(SOURCES InetAddress.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR})
