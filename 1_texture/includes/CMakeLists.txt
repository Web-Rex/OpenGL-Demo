# ----- [ Utilities ] -----
file(GLOB_RECURSE UTILITIES_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utilities/src/*.cpp")

add_library(utilities ${UTILITIES_SOURCES})
target_include_directories(utilities
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utilities/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/utilities/src
    # PUBLIC  ${CMAKE_BINARY_DIR}/configured/include
)
target_link_libraries(utilities PRIVATE glad stb_image)