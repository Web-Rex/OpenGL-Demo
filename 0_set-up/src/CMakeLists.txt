# [...]
copy_files("${CMAKE_SOURCE_DIR}/resources/shaders/*.fs" "${CMAKE_BINARY_DIR}/resources/shaders" "./main.cpp")
copy_files("${CMAKE_SOURCE_DIR}/resources/shaders/*.vs" "${CMAKE_BINARY_DIR}/resources/shaders" "./main.cpp")
# copy_files("${CMAKE_SOURCE_DIR}/recourses/texture/*.png" "${CMAKE_BINARY_DIR}/recourses/texture" "./main.cpp")



# [...]
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} glfw glad)