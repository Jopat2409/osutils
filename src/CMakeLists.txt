cmake_minimum_required(VERSION 3.7)
include(GenerateExportHeader)

if(BUILD_FOR_PYTHON)
    pybind11_add_module(osutils pymodule.cpp)
else()
    add_library(osutils SHARED "")
endif()

target_include_directories(osutils
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/osutils/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/osutils/>
        $<INSTALL_INTERFACE:include/osutils/>
)


generate_export_header(osutils EXPORT_MACRO_NAME OSU_API)

target_sources(osutils
    PRIVATE
        db.cpp
        beatmap.cpp
        osu_utils.cpp
)
