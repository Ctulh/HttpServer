set(LIB_NAME InetLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Inet)

set(CORO_LIB Coroutines)
set(CORO_LIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Utils/Coroutines)

set(HEADERS ${INCLUDE_DIR}/InetAddress.hpp
            ${INCLUDE_DIR}/Socket.hpp
            ${INCLUDE_DIR}/TcpServer.hpp
            ${INCLUDE_DIR}/TcpConnection.hpp
            ${INCLUDE_DIR}/ConnectionAcceptor.hpp
            ${INCLUDE_DIR}/callbacks.hpp
            ${INCLUDE_DIR}/SocketPoller.hpp)

set(SOURCES InetAddress.cpp
            Socket.cpp
            TcpConnection.cpp
            ConnectionAcceptor.cpp
            SocketReader.cpp
            SocketPoller.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${LIB_NAME} PRIVATE ${CORO_LIB})


target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR} ${CORO_LIB_INCLUDE_DIR})
