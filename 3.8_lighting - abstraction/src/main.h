#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "glfw-lib/window.h"
#include "glfw-lib/camera.h"

#include "gl-lib/shader.h"
#include "gl-lib/texture.h"
#include "gl-lib/light.h"

#include "utils-lib/keys.h"



// // [...] glfw: whenever the mouse scroll wheel scrolls, this callback is called
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//     fov -= (float)yoffset;
//     if (fov < 1.0f)
//         fov = 1.0f;
//     if (fov > 45.0f)
//         fov = 45.0f;
// }