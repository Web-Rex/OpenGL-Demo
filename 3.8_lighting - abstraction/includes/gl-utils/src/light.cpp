#include "../gl-lib/light.h"



Light::Light(const Shader &shader, int diffuse, int specular, float shininess, glm::vec3 cPos)
{
    shader.Set_Uniform_Int("material.diffuse", diffuse);
    shader.Set_Uniform_Int("material.specular", specular);
    shader.Set_Uniform_Float("material.shininess", shininess);
    shader.Set_Uniform_3Float("viewPos", cPos.x, cPos.y, cPos.z);
};

Light::~Light() {}

void Light::Direction_Light(const Shader &shader, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    shader.Set_Uniform_Int("useDirLight", 1);
    shader.Set_Uniform_3Float("dirLight.direction", direction.x, direction.y, direction.z);
    shader.Set_Uniform_3Float("dirLight.ambient", ambient.x, ambient.y, ambient.z);
    shader.Set_Uniform_3Float("dirLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
    shader.Set_Uniform_3Float("dirLight.specular", specular.x, specular.y, specular.z);
}

void Light::Point_Light(const Shader &shader, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
{
    shader.Set_Uniform_Int("usePointLights", 1);
    shader.Set_Uniform_3Float("pointLights.position", position.x, position.y, position.z);
    shader.Set_Uniform_3Float("pointLights.ambient", ambient.x, ambient.y, ambient.z);
    shader.Set_Uniform_3Float("pointLights.diffuse", diffuse.x, diffuse.y, diffuse.z);
    shader.Set_Uniform_3Float("pointLights.specular", specular.x, specular.y, specular.z);
    shader.Set_Uniform_Float("pointLights.constant", constant);
    shader.Set_Uniform_Float("pointLights.linear", linear);
    shader.Set_Uniform_Float("pointLights.quadratic", quadratic);
}

void Light::Spot_Light(const Shader &shader, glm::vec3 lightPos, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
{
    shader.Set_Uniform_Int("useSpotLight", 1);
    shader.Set_Uniform_3Float("spotLight.position", lightPos.x, lightPos.y, lightPos.z);
    shader.Set_Uniform_3Float("spotLight.direction", direction.x, direction.y, direction.z);
    shader.Set_Uniform_3Float("spotLight.ambient", ambient.x, ambient.y, ambient.z);
    shader.Set_Uniform_3Float("spotLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
    shader.Set_Uniform_3Float("spotLight.specular", specular.x, specular.y, specular.z);
    shader.Set_Uniform_Float("spotLight.constant", constant);
    shader.Set_Uniform_Float("spotLight.linear", linear);
    shader.Set_Uniform_Float("spotLight.quadratic", quadratic);
    shader.Set_Uniform_Float("spotLight.cutOff", cutOff);
    shader.Set_Uniform_Float("spotLight.outerCutOff", outerCutOff);
}