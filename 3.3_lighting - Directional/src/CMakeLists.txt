# [...]
copy_files("${CMAKE_SOURCE_DIR}/resources/shaders/*.fs"         "${CMAKE_BINARY_DIR}/resources/shaders" "./main.cpp")
copy_files("${CMAKE_SOURCE_DIR}/resources/shaders/*.vs"         "${CMAKE_BINARY_DIR}/resources/shaders" "./main.cpp")
copy_files("${CMAKE_SOURCE_DIR}/resources/textures/*.jpg"       "${CMAKE_BINARY_DIR}/resources/textures" "./main.cpp")
copy_files("${CMAKE_SOURCE_DIR}/resources/textures/*.png"       "${CMAKE_BINARY_DIR}/resources/textures" "./main.cpp")



# [...]
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    # [...]
    ${OPENGL_LIBRARIES} glfw glad glm
    # [...]
    utils
    gl_utils
    glfw_utils
)