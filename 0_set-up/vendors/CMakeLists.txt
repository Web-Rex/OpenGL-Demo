# [...] include-f-content
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)


# [...] openGL
find_package(OpenGL REQUIRED)


# [...] glfw Cmake-3.11
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "x" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "x" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "x" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
#     GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glfw) # Cmake-3.14


# [...] glfw Cmake-3.11
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
#     GIT_PROGRESS TRUE
)

set(GLAD_PROFILE "core"	CACHE STRING "OpenGL profile")
set(GLAD_GENERATOR "c"	CACHE STRING "Language to generate the binding for")
FetchContent_MakeAvailable(glad)