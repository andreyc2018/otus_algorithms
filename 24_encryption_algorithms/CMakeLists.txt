cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_BUILD_TYPE Debug)

project(algorithms-24_encryption_algorithms)

find_package(Threads REQUIRED)

#set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)
#set(GTEST_DIR ${COURSE_DIR}/googletest)

#include_directories(${CMAKE_CURRENT_BINARY_DIR}
#        ${COURSE_DIR}/include)
#        ${GTEST_DIR}/googletest/include
#        ${GTEST_DIR}/googlemock/include)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES xorcrypt.h)

add_library(xorcrypt STATIC xorcrypt.cpp key.cpp ${HEADER_FILES} README.md)

add_executable(encrypt_xor-bin encrypt_xor_main.cpp ${HEADER_FILES})
target_compile_options(encrypt_xor-bin PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(encrypt_xor-bin xorcrypt)
set_target_properties(encrypt_xor-bin PROPERTIES OUTPUT_NAME encrypt_xor)

add_executable(decrypt_xor-bin decrypt_xor_main.cpp ${HEADER_FILES})
target_compile_options(decrypt_xor-bin PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(decrypt_xor-bin xorcrypt)
set_target_properties(decrypt_xor-bin PROPERTIES OUTPUT_NAME decrypt_xor)

add_executable(test_xorcrypt test_xorcrypt.cpp catch.hpp ${HEADER_FILES})
target_compile_options(test_xorcrypt PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(test_xorcrypt xorcrypt)

include(CPack)

# Add googltest
#if(EXISTS ${GTEST_DIR}/CMakeLists.txt)
#    # Replace install() to do-nothing macro.
#    macro(install)
#    endmacro()
#    # Include subproject (or any other CMake code) with "disabled" install().
#    message(STATUS "Adding Google Test framework.")
#    add_subdirectory(${GTEST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/googletest)
#    # Restore original install() behavior.
#    macro(install)
#        _install(${ARGN})
#    endmacro()
#endif()

