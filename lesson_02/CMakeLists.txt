cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

if ($ENV{TRAVIS_BUILD_NUMBER})
    set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(BUILD_NUM 99)
endif()

set(homework_VERSION_MAJOR 2)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD ${BUILD_NUM})

project(async VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Threads REQUIRED)

configure_file(version.h.in version.h)

set(COURSE_DIR ${CMAKE_SOURCE_DIR}/..)
set(GTEST_DIR ${COURSE_DIR}/googletest)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
        ${GTEST_DIR}/googletest/include
        ${GTEST_DIR}/googlemock/include)

set(HEADER_FILES
        DArray.h BArray.h DBArray.h)

add_executable(darray darray.cpp ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)
add_executable(test_priority_queue test_priority_queue.cpp)
add_executable(test_barray test_barray.cpp)

target_compile_options(darray PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_priority_queue PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_barray PRIVATE -Wpedantic -Wall -Wextra)

target_link_libraries(test_priority_queue gmock_main Threads::Threads)
target_link_libraries(test_barray gmock_main Threads::Threads)

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

# add_subdirectory(example)

# if(EXISTS ${CMAKE_SOURCE_DIR}/sandbox/CMakeLists.txt)
#     add_subdirectory(sandbox EXCLUDE_FROM_ALL)
# endif()

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

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/docs)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/README.md
                ${CMAKE_CURRENT_BINARY_DIR}/docs/README.md COPYONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/hw_assignment.md
                ${CMAKE_CURRENT_BINARY_DIR}/docs/hw_assignment.md COPYONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/_config.yml
                ${CMAKE_CURRENT_BINARY_DIR}/docs/_config.yml COPYONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/parser_state_machine.uml
                ${CMAKE_CURRENT_BINARY_DIR}/docs/parser_state_machine.uml COPYONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/parser_state_machine.png
                ${CMAKE_CURRENT_BINARY_DIR}/docs/html/parser_state_machine.png COPYONLY)
    
        # note the option ALL which allows to build the docs together with the application
        #add_custom_target(doc_doxygen ALL
        add_custom_target(doc_doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    else(DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif(DOXYGEN_FOUND)
endif()

