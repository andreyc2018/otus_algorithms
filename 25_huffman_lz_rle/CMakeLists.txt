cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_BUILD_TYPE Debug)

project(algorithms-25_huffman_lz_rle)

find_package(Threads REQUIRED)

set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES avltree.h)

add_library(rle_compress STATIC rle_compress.cpp ${HEADER_FILES} README.md)

add_executable(test_avltree test_avltree.cpp ${HEADER_FILES})
target_compile_options(test_avltree PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(test_avltree avltree gtest_main Threads::Threads)

include(CPack)
