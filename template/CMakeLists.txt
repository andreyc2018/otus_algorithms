cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_BUILD_TYPE Debug)

project(algorithms-N_lesson_title)

find_package(Threads REQUIRED)

set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)
set(GTEST_DIR ${COURSE_DIR}/googletest)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
        ${COURSE_DIR}/include
        ${GTEST_DIR}/googletest/include
        ${GTEST_DIR}/googlemock/include)

set(HEADER_FILES xorcrypt.h)

add_library(xorcrypt STATIC xorcrypt.cpp ${HEADER_FILES} README.md)

add_executable(xorcrypt-bin xorcrypt_main.cpp ${HEADER_FILES})
target_compile_options(xorcrypt-bin PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(xorcrypt-bin xorcrypt)
set_target_properties(xorcrypt-bin PROPERTIES OUTPUT_NAME xorcrypt)

add_executable(test_xorcrypt test_xorcrypt.cpp ${HEADER_FILES})
target_compile_options(test_xorcrypt PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(test_xorcrypt xorcrypt gtest_main)

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


