#include <iostream>
#include <vector>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils-lib/keys.h"

#include "../glfw-lib/window.h"


namespace
{
    GLFWwindow *_id;
} // namespace


Window::Window(/* args */)
{
    // [...] init-glfw
    if (!glfwInit())
        std::cout << "GLFW init failed \n";

    // [...] opengl-version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // [...] glfw-window
    _id = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (_id == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // [...] get-buffer-size-info
    glfwGetFramebufferSize(_id, &_buffer_width, &_buffer_height);

    glfwMakeContextCurrent(_id);

    // [...] init-glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "Failed to initialize GLAD \n";

    // [...] configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // [...] storing user-window ass a pointer in glfw
    glfwSetWindowUserPointer(_id, this);

    // [...] tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::Get_Window_Should_Close()
{
    return glfwWindowShouldClose(_id);
}

void Window::Close_Window()
{
    return glfwSetWindowShouldClose(_id, true);
}

void Window::Swap_Buffers()
{
    glfwSwapBuffers(_id);
}

void Window::Set_CallBack()
{
    glfwSetFramebufferSizeCallback(_id, Handle_Resize);
    glfwSetKeyCallback(_id, Handle_Keys);
    glfwSetCursorPosCallback(_id, Handle_Mouse);
    // glfwSetScrollCallback(_id, Handle_Scroll);
}

void Window::Handle_Keys(GLFWwindow *window, int key, int code, int action, int mode)
{
    EVENTS::Handle_Keys_Events(key, action);
}

void Window::Handle_Resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::Handle_Scroll(GLFWwindow* window, double x_offset, double y_offset)
{
    // EVENTS::Handle_Mouse_Events(static_cast<float>(x_offset), static_cast<float>(y_offset));
}

void Window::Handle_Mouse(GLFWwindow* window, double x_posIn, double y_posIn)
{
    EVENTS::Handle_Mouse_Events(static_cast<float>(x_posIn), static_cast<float>(y_posIn));
}