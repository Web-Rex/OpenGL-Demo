#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"







// [...]
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << window << "\n";
    glViewport(0, 0, width, height);
}

// [...]
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}