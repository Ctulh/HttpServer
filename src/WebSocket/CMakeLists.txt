set(LIB_NAME WebSocketLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/WebSocket)

set(HEADERS ${INCLUDE_DIR}/IWebSocketConnection.hpp
            ${INCLUDE_DIR}/IWebSocket.hpp
            WebSocketConnectionImpl.hpp)

set(SOURCES WebSocketConnectionImpl.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR})
