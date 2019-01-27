cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_BUILD_TYPE Debug)

if ($ENV{TRAVIS_BUILD_NUMBER})
    set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(BUILD_NUM 99)
endif()

set(homework_VERSION_MAJOR 5)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD ${BUILD_NUM})

project(algorithms_lesson-05 VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Threads REQUIRED)

configure_file(version.h.in version.h)

set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)
set(GTEST_DIR ${COURSE_DIR}/googletest)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
        ${COURSE_DIR}/include
        ${GTEST_DIR}/googletest/include
        ${GTEST_DIR}/googlemock/include)

add_executable(test_heapsort test_heapsort.cpp heapsort.h)
target_compile_options(test_heapsort PRIVATE -Wpedantic -Wall -Wextra)
target_link_libraries(test_heapsort gtest_main Threads::Threads)

include(CPack)
enable_testing()
add_test(NAME power COMMAND test_heapsort)

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

message(STATUS "Homework version
    ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD}")

