#version 330 core

in vec3 ourVColor; // we set this variable in the OpenGL code.
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 ourColor; // we set this variable in the OpenGL code.

out vec4 FragColor;

void main()
{
    // FragColor = vec4(ourVColor.x, ourColor.y, ourVColor.z, 1.0);
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(ourVColor.x, ourColor.y, ourVColor.z, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
}