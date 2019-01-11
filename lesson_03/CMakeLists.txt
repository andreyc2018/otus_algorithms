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

set(homework_VERSION_MAJOR 3)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD ${BUILD_NUM})

project(async VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Threads REQUIRED)

configure_file(version.h.in version.h)

set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)
set(GTEST_DIR ${COURSE_DIR}/googletest)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
        ${COURSE_DIR}/include
        ${GTEST_DIR}/googletest/include
        ${GTEST_DIR}/googlemock/include)

set(HEADER_FILES
        DArray.h BArray.h DBArray.h ${COURSE_DIR}/include/stopwatch.h)

add_executable(darray darray.cpp ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)
add_executable(test_priority_queue test_priority_queue.cpp PriorityQueue.h)
add_executable(test_barray test_barray.cpp BArray.h)
add_executable(test_olist test_olist.cpp OList.h)
add_executable(test_iarray test_iarray.cpp IArray.h)

target_compile_options(darray PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_priority_queue PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_barray PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_olist PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_iarray PRIVATE -Wpedantic -Wall -Wextra)

target_link_libraries(test_priority_queue gmock_main Threads::Threads)
target_link_libraries(test_barray gmock_main Threads::Threads)
target_link_libraries(test_olist gmock_main Threads::Threads)
target_link_libraries(test_iarray gmock_main Threads::Threads)

# install(TARGETS async LIBRARY DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT "sysdos286@yahoo.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${homework_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${homework_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${homework_VERSION_BUILD})

include(CPack)

enable_testing()

add_test(NAME priority_queue COMMAND test_priority_queue)
add_test(NAME barray COMMAND test_barray)
add_test(NAME olist COMMAND test_olist)
add_test(NAME iarray COMMAND test_iarray)

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
