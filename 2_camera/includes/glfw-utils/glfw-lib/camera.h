#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
private:
    glm::vec3 camera_pos, camera_dir, camera_up;
    bool first_mouse;
    float yaw, pitch, last_x, last_y, fov, delta_time, last_frame;

public:
    Camera(glm::vec3 c_pos, glm::vec3 c_dir, glm::vec3 c_up);
    ~Camera();

    void Camera_Arrow_Key_M(float camera_speed);
    void Camera_Mouse_M(float sensitivity);

    glm::mat4 Get_View_M() const { return glm::lookAt(camera_pos, camera_pos + camera_dir, camera_up); };
};