#include "main.h"


// [...] timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// [...] lighting
glm::vec3 lightPos(1.0f, 0.8f, 1.5f);


int main()
{
    // [...] init-glfw
    Window glfw_window;
    glfw_window.Set_CallBack();

    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera.Camera_Arrow_Key_M(0.005f);
    camera.Camera_Mouse_M(0.01f);

    // [...] events
    EVENTS::Add_Keys_Event([&glfw_window](int key, unsigned int* action) {
        if (action[KEY_ESCAPE] == KEY_PRESS)
            glfw_window.Close_Window();
    }, "Close_Window");


    // [...] ==========================================================================================


    // [...] shader
    Shader shader1("resources/shaders/shader.vs", "resources/shaders/shader.fs"); // you can name your shader files however you like
    Shader shader2("resources/shaders/light.vs", "resources/shaders/light.fs"); // you can name your shader files however you like

    // [...] vertex
    float vertices[] = {
        //  - pos -
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // ========== [...] shader

    // [...] vao
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // [...] vbo
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // [...] vertex-attrib-array - vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ========== [...] light

    // [...] vao
    unsigned int VAO_LIGHT;
    glGenVertexArrays(1, &VAO_LIGHT);
    glBindVertexArray(VAO_LIGHT);

    // [...] vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // [...] vertex-attrib-array - vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // [...] ==========================================================================================

    // [...] glfw-render-loop
    while(!glfw_window.Get_Window_Should_Close())
    {
        // [...] per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // [...] rendering commands here
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth buffer before each render iteration (otherwise the depth information of the previous frame stays in the buffer)

        // ========== [...] shader1
        shader1.Bind();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), glfw_window.Get_Width() / glfw_window.Get_Height(), 0.1f, 100.0f);

        glm::mat4 trans(1.0f);
        // trans = glm::translate(trans, glm::vec3(0.0f,  0.0f,  0.0f));
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()) * glm::radians(90.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(1.0, 1.0, 1.0));

        shader1.Set_Uniform_4FMatrix("mvp", (projection * camera.Get_View_M() * trans));
        shader1.Set_Uniform_4FMatrix("model", trans);
        shader1.Set_Uniform_4FMatrix("trans", glm::transpose(glm::inverse(trans))); // so our lighting will not brake when we scale.
        shader1.Set_Uniform_3Float("viewPos", camera.Get_Camera_Pos().x, camera.Get_Camera_Pos().y, camera.Get_Camera_Pos().z);

        shader1.Set_Uniform_3Float("material.ambient", 1.0f, 0.5f, 0.31f);
        shader1.Set_Uniform_3Float("material.diffuse", 1.0f, 0.5f, 0.31f);
        shader1.Set_Uniform_3Float("material.specular", 0.5f, 0.5f, 0.5f);
        shader1.Set_Uniform_Float("material.shininess", 32.0f);

        glm::vec3 shapeCol(0.91f, 0.024f, 0.365f);
        glm::vec3 ambient = shapeCol * glm::vec3(0.2f);
        glm::vec3 diffuse = shapeCol * glm::vec3(0.5f);

        shader1.Set_Uniform_3Float("light.ambient",  ambient.x, ambient.y, ambient.z);
        shader1.Set_Uniform_3Float("light.diffuse",  diffuse.x, diffuse.y, diffuse.z); // darken diffuse light a bit
        shader1.Set_Uniform_3Float("light.specular", 1.0f, 1.0f, 1.0f);
        shader1.Set_Uniform_3Float("light.position", lightPos.x, lightPos.y, lightPos.z);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ========== [...] shader2
        shader2.Bind();

        trans = 1.0f;
        trans = glm::translate(trans, lightPos);
        trans = glm::scale(trans, glm::vec3(0.05, 0.05, 0.05));

        shader1.Set_Uniform_4FMatrix("mvp", (projection * camera.Get_View_M() * trans));

        glBindVertexArray(VAO_LIGHT); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glBindVertexArray(0); // no need to unbind it every time

        // [...] check and call events and swap the buffers
        glfwPollEvents();
        glfw_window.Swap_Buffers();
    }

    // [...] optional: de-allocate all resources once they've outlived their purpose:
    // [...] ========================================

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAO_LIGHT);
    glDeleteBuffers(1, &VBO);

    // [...] ========================================


    // [...] destroy-glfw
    glfwTerminate();
    return 0;
}