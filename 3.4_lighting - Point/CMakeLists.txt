cmake_minimum_required(VERSION 3.21)

project(
        3_4_lighting
        VERSION 0.0.1
        DESCRIPTION "A Simple 'sand-box' Application"
        LANGUAGES C CXX
)

# [...] variables
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
option(ENABLE_WARNINGS "Enable To Add Warnings To A Target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable To Treat Warnings As Errors." OFF)
option(GEN_GRAPHVIZ_PNG "Generate Dependencies Graph." ON)
option(ENABLE_LTO "Enable To Add Link Time Optimization." ON)


# [...] config-utilities-cmake
include(utilities)


# [...] sub-dir
add_subdirectory(vendors)
add_subdirectory(includes)
add_subdirectory(src)


# [...] config-dot-cmake
include(utils)