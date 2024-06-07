# ----- [ Utils ] -----
file(GLOB_RECURSE UTILS_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/src/*.cpp")
# file(GLOB_RECURSE UTILS_HEADERS CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/utils-lib/*.h")
add_library(utils ${UTILS_SOURCES})
target_include_directories(utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utils
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/utils/src
)


# ----- [ Utilities ] -----
file(GLOB_RECURSE GL_LIB_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/gl-utils/src/*.cpp")

add_library(gl_utils ${GL_LIB_SOURCES})
target_include_directories(gl_utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gl-utils
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gl-utils/src
    # PUBLIC  ${CMAKE_BINARY_DIR}/configured/include
)
target_link_libraries(gl_utils PRIVATE glad stb_image glm)


# ----- [ glfw-Utilities ] -----
file(GLOB_RECURSE GLFW_UTILS_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glfw-utils/src/*.cpp")

add_library(glfw_utils ${GLFW_UTILS_SOURCES})
target_include_directories(glfw_utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw-utils
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw-utils/src
    # PUBLIC  ${CMAKE_BINARY_DIR}/configured/include
)
target_link_libraries(glfw_utils PRIVATE glfw glad glm utils)