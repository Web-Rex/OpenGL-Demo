#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>


#include <glad/glad.h>
#include <GLFW/glfw3.h>




// [...]
std::string load_shader(const char *filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if (file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }
    else
    {
        std::cout << "Could not open " << filename << std::endl;
    }

    file.close();

    return ret;
}

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