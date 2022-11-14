set(TARGET_NAME tests)

set(SOURCE main_test.cpp)

add_executable(${TARGET_NAME} ${SOURCE})

target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS_GTEST})
