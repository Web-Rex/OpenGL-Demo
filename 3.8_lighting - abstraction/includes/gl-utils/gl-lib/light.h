#pragma once

#include <glm/glm.hpp>

#include "./shader.h"

class Light
{
public:
    Light(const Shader &shader, int diffuse, int specular, float shininess, glm::vec3 cPos);
    ~Light();

    static void Direction_Light(const Shader &shader, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void Point_Light(const Shader &shader, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    void Spot_Light(const Shader &shader, glm::vec3 lightPos, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff);
};