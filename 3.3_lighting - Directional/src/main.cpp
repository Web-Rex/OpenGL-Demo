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
    //  -positions              -normals                -texture coords
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -  1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -  1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -  1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -  1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -  1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -  1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // ========== [...] light

    // [...] vao
    unsigned int VAO_LIGHT;
    glGenVertexArrays(1, &VAO_LIGHT);
    glBindVertexArray(VAO_LIGHT);

    // [...] vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // [...] vertex-attrib-array - vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ========== [...] texture
    Texture texture1("resources/textures/png-5.png"); // diffuse map
    Texture texture2("resources/textures/png-6.png"); // specular map

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


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

        shader1.Set_Uniform_3Float("viewPos", camera.Get_Camera_Pos().x, camera.Get_Camera_Pos().y, camera.Get_Camera_Pos().z);

        shader1.Set_Uniform_Int("material.diffuse", 0);
        shader1.Set_Uniform_Int("material.specular", 1);
        shader1.Set_Uniform_Float("material.shininess", 64.0f);

        shader1.Set_Uniform_3Float("light.ambient",  0.2f, 0.2f, 0.2f);
        shader1.Set_Uniform_3Float("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        shader1.Set_Uniform_3Float("light.specular", 1.0f, 1.0f, 1.0f);
        shader1.Set_Uniform_3Float("light.direction", -0.2f, -1.0f, -0.3f);

        texture1.Bind(0);
        texture2.Bind(1);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 trans(1.0f);
            trans = glm::translate(trans, cubePositions[i]);
            float angle = 20.0f * static_cast<float>(i);

            trans = glm::rotate(trans, (static_cast<float>(glfwGetTime()) * 0.1f) * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            trans = glm::scale(trans, glm::vec3(1.0, 1.0, 1.0));

            shader1.Set_Uniform_4FMatrix("mvp", (projection * camera.Get_View_M() * trans));
            shader1.Set_Uniform_4FMatrix("model", trans);
            shader1.Set_Uniform_4FMatrix("trans", glm::transpose(glm::inverse(trans))); // so our lighting will not brake when we scale.

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ========== [...] shader2
        // [...] a lamp object is weird when we only have a directional light, don't render the light object, cause Directional lights are great for global lights that illuminate the entire scene
        // shader2.Bind();

        // glm::mat4 trans(1.0f);
        // trans = glm::translate(trans, lightPos);
        // trans = glm::scale(trans, glm::vec3(0.05, 0.05, 0.05));

        // shader1.Set_Uniform_4FMatrix("mvp", (projection * camera.Get_View_M() * trans));

        // glBindVertexArray(VAO_LIGHT); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 36);

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