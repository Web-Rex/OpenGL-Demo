#version 330 core
out vec4 FragColor;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec3 fragPos;
in vec3 normal;
in vec2 texCord;

uniform vec3 viewPos;
uniform Material material;

// [...] light casters
uniform DirLight dirLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform SpotLight spotLight;


// [...] light implementation
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCord));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
        light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, texCord).rgb;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCord).rgb;

    // specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.specular, texCord).rgb);

        // point-light
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        // soft-spot-light
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    ambient *= attenuation;
    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}

void main() {
    // properties
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);

    // phase 3: Spot light
    result += CalcSpotLight(spotLight, norm, fragPos, viewDir);

    FragColor = vec4(result, 1.0);
}