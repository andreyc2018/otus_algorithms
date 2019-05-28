cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_BUILD_TYPE Debug)

project(algorithms-03_programming_chess)

find_package(Threads REQUIRED)

set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)
set(GTEST_DIR ${COURSE_DIR}/googletest)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
        ${COURSE_DIR}/include
        ${GTEST_DIR}/googletest/include
        ${GTEST_DIR}/googlemock/include)

add_executable(knight_moves knight_moves.cpp README.md)
target_compile_options(knight_moves PRIVATE -Wpedantic -Wall -Wextra)

add_executable(get_knight_moves get_knight_moves.cpp)
target_compile_options(get_knight_moves PRIVATE -Wpedantic -Wall -Wextra)

set(HEADER_FILES fen_parser.h)
add_executable(parse_fen parse_fen.cpp ${HEADER_FILES} Шахматные_тесты-19350-882833.txt)
target_compile_options(parse_fen PRIVATE -Wpedantic -Wall -Wextra)

add_executable(test_parse_fen test_parse_fen.cpp ${HEADER_FILES})
target_compile_options(test_parse_fen PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(test_parse_fen gtest_main Threads::Threads)

include(CPack)

# Add googltest
if(EXISTS ${GTEST_DIR}/CMakeLists.txt)
    # Replace install() to do-nothing macro.
    macro(install)
    endmacro()
    # Include subproject (or any other CMake code) with "disabled" install().
    message(STATUS "Adding Google Test framework.")
    add_subdirectory(${GTEST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/googletest)
    # Restore original install() behavior.
    macro(install)
        _install(${ARGN})
    endmacro()
endif()

