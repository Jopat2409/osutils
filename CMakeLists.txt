cmake_minimum_required(VERSION 3.7)

if(${CMAKE_VERSION} VERSION_LESS 3.27)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.27)
endif()

option(BUILD_FOR_PYTHON "Build this project as a python module" OFF)
option(BUILD_TESTS "Build the testing suite for this module" OFF)

#option(BUILD_STATIC_LIBS "Build this module as a static library" ON)
#option(BUILD_SHARED_LIBS "Build this module as a Dynamic-Link Library" ON)
#option(BUILD_TESTS "Build the tests for this module" OFF)


project(OsuUtils VERSION 1.0
          DESCRIPTION "Utilities for interacting with osu binary files"
            LANGUAGES CXX)

add_compile_definitions(MS_WINDOWS=1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

if(BUILD_FOR_PYTHON)
    add_subdirectory(extern/pybind11)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
    target_link_libraries(osutils_test PUBLIC osutils)
endif()

