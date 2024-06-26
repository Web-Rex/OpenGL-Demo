#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;

out vec3 normal;
out vec3 fragPos;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(trans) * aNormal;
}