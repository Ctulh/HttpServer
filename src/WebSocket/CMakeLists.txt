set(LIB_NAME WebSocketLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/WebSocket)

set(HEADERS ${INCLUDE_DIR}/IWebSocketConnection.hpp
            ${INCLUDE_DIR}/IWebSocket.hpp
            WebSocketConnectionImpl.hpp)

set(SOURCES )


add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR})
