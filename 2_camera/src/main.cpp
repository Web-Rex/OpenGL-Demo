#include "main.h"

// glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);


// bool firstMouse = true;
// float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
// float pitch =  0.0f;
// float lastX =  800.0f / 2.0;
// float lastY =  600.0 / 2.0;
// float fov   =  45.0f;


// // [...] timing
// float deltaTime = 0.0f;	// Time between current frame and last frame
// float lastFrame = 0.0f; // Time of last frame


int main()
{
    // [...] init-glfw
    Window glfw_window;
    glfw_window.Set_CallBack();

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera.Camera_Arrow_Key_M(0.05f);
    camera.Camera_Mouse_M(0.1f);

    // [...] events
    EVENTS::Add_Keys_Event([&glfw_window](int key, unsigned int* action) {
        if (action[KEY_ESCAPE] == KEY_PRESS)
            glfw_window.Close_Window();
    }, "Close_Window");


    // [...] ==========================================================================================

    // [...] shader
    Shader ourShader("resources/shaders/shader.vs", "resources/shaders/shader.fs"); // you can name your shader files however you like

    // [...] vertex
    float vertices[] = {
    //  - pos -                   - texture -
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,        1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,        1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,        1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,        1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,        1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,        1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f,
    };
    unsigned int indices[] = {  // note that we start from 0!
        0,   1,  2,
        2,   3,  0,
        4,   5,  6,
        6,   7,  4,
        8,   9,  10,
        10,  4,  8,
        11,  2,  12,
        13,  14, 11,
        10,  15, 5,
        5,   4,  10,
        3,   2,  11,
        11,  16, 3,
    };
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

    // [...] vao
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // [...] vbo
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // [...] ebo
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // [...] vertex-attrib-array - vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // [...] vertex-attrib-array - texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    // [...] textures
    Texture texture1("resources/textures/img-3.jpg");


    // [...] note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // [...] remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // [...] You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // [...] VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wire-frame polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // [...] ==========================================================================================

    // [...] glfw-render-loop
    while(!glfw_window.Get_Window_Should_Close())
    {
        // [..] per-frame time logic
        // float currentFrame = static_cast<float>(glfwGetTime());
        // deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        // [...] rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth buffer before each render iteration (otherwise the depth information of the previous frame stays in the buffer)

        ourShader.Bind();

        // [...]
        // glm::mat4 view = glm::mat4(1.0f);
        // const float radius = 10.0f;

        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;
        // [ camera position ] : [ a target position ] : [ a vector that represents the up vector in world space (the up vector we used for calculating the right vector) ]
        // view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), glfw_window.Get_Width() / glfw_window.Get_Height(), 0.1f, 100.0f);

        // [...] texture
        texture1.Bind();

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        for(unsigned int i = 0; i < 10; i++)
        {
            float angle = i == 0 ? 20.0f : 10.0f * i;

            glm::mat4 trans(1.0f);
            trans = glm::translate(trans, glm::vec3(cubePositions[i]));
            trans = glm::rotate(trans, static_cast<float>(glfwGetTime()) * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
            trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

            ourShader.Set_Uniform_4FMatrix("mvp", (projection * camera.Get_View_M() * trans));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // glBindVertexArray(0); // no need to unbind it every time

        // [...] check and call events and swap the buffers
        glfwPollEvents();
        glfw_window.Swap_Buffers();
    }

    // [...] optional: de-allocate all resources once they've outlived their purpose:
    // [...] ========================================

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // [...] ========================================


    // [...] destroy-glfw
    glfwTerminate();
    return 0;
}