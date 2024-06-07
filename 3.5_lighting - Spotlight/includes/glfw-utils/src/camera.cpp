#include "utils-lib/keys.h"

#include <GLFW/glfw3.h>

#include "../glfw-lib/camera.h"



Camera::Camera(glm::vec3 c_pos, glm::vec3 c_dir, glm::vec3 c_up) : camera_pos(c_pos), camera_dir(c_dir), camera_up(c_up)
{
    yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    pitch =  0.0f;
    fov   =  45.0f;
    first_mouse = true;
    delta_time = 0.0f;
    last_frame = 0.0f;
    last_x =  800.0f / 2.0;
    last_y =  600.0 / 2.0;
}

Camera::~Camera() {
    EVENTS::Delete_Keys_Event("camera_position");
    EVENTS::Delete_Mouse_Event("Camera_Mouse_Move");
}

void Camera::Camera_Arrow_Key_M(float camera_speed)
{
    EVENTS::Add_Keys_Event([&c_pos = camera_pos, &c_dir = camera_dir, &c_up = camera_up, camera_speed](int key, unsigned int* action)
        {
            // std::cout << " --- " << c_pos.x << " , " << c_pos.y << " , " << c_pos.z << " --- " << camera_speed << "\n";
            const float cameraSpeed = camera_speed * static_cast<float>(glfwGetTime()); // adjust accordingly

            if (action[GLFW_KEY_LEFT_SHIFT] == GLFW_REPEAT)
                {
                    if (key == GLFW_KEY_UP & action[key] == GLFW_REPEAT)
                            c_pos += c_up * cameraSpeed;
                    if (key == GLFW_KEY_DOWN & action[key] == GLFW_REPEAT)
                            c_pos -= c_up * cameraSpeed;
                }

            else if (action[GLFW_KEY_SPACE] == GLFW_REPEAT) {}

            else {
                if (action[GLFW_KEY_UP] == GLFW_REPEAT)
                    c_pos += cameraSpeed * c_dir;
                if (action[GLFW_KEY_DOWN] == GLFW_REPEAT)
                    c_pos -= cameraSpeed * c_dir;
                if (action[GLFW_KEY_LEFT] == GLFW_REPEAT)
                    c_pos -= glm::normalize(glm::cross(c_dir, c_up)) * cameraSpeed;
                if (action[GLFW_KEY_RIGHT] == GLFW_REPEAT)
                    c_pos += glm::normalize(glm::cross(c_dir, c_up)) * cameraSpeed;
            }
        }, "camera_position");
}

void Camera::Camera_Mouse_M(float sensitivity)
{
    EVENTS::Add_Mouse_Event([&first_m = first_mouse, &l_x = last_x, &l_y = last_y, &_pitch = pitch, &_yaw = yaw, &camera_d = camera_dir, sensitivity] (float x_pos, float y_pos)
    {
        if (first_m)
        {
            l_x = x_pos;
            l_y = y_pos;
            first_m = false;
        }

        float x_offset = x_pos - l_x;
        float y_offset = l_y - y_pos; // reversed since y-coordinates go from bottom to top
        l_x = x_pos;
        l_y = y_pos;

        x_offset *= sensitivity;
        y_offset *= sensitivity;

        _yaw += x_offset;
        _pitch += y_offset;

        // std::cout << "yaw: " << _yaw << " pitch: " << _pitch << "\n";

        // [...] make sure that when pitch is out of bounds, screen doesn't get flipped
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        camera_d = glm::normalize(front);
    }, "Camera_Mouse_Move");
}