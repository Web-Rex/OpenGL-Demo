
#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "../gl-lib/shader.h"

std::string Shader::Load_Shader(const char *filename)
{
    std::ifstream file;
    std::string ret = "";

    // [...] ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // [...] open files
        file.open(filename);

        // [...] read file's buffer contents into streams
        std::stringstream buf;
        buf << file.rdbuf();

        // [..] close file handlers
        file.close();
        // [...] convert stream into string
        ret = buf.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::" << filename << "::FILE_NOT_SUCCESSFULLY_READ\n";
        std::cerr << e.what() << '\n';
    }

    return ret;
}

unsigned int Shader::Compile_Shader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // [...] Error-Handle
    glGetShaderiv(id, GL_COMPILE_STATUS, &_success);
    if (!_success)
    {
        glGetShaderInfoLog(id, 512, NULL, _infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << _infoLog << std::endl;
    }

    return id;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    _id = glCreateProgram();

    unsigned int vShaderCode = Compile_Shader(GL_VERTEX_SHADER, Load_Shader(vertexPath));
    unsigned int fShaderCode = Compile_Shader(GL_FRAGMENT_SHADER, Load_Shader(fragmentPath));

    glAttachShader(_id, vShaderCode);
    glAttachShader(_id, fShaderCode);
    glLinkProgram(_id);

    glGetProgramiv(_id, GL_LINK_STATUS, &_success);
    if (!_success)
    {
        glGetProgramInfoLog(_id, 512, NULL, _infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << _infoLog << std::endl;
    }

    glDeleteShader(vShaderCode);
    glDeleteShader(fShaderCode);
}

void Shader::Bind() const
{
    glUseProgram(_id);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::Set_Uniform_Bool(const std::string &name, bool value) const
{
    glUniform1i(Get_Uniform_Location(name), (int)value);
}
void Shader::Set_Uniform_Int(const std::string &name, int value) const
{
    glUniform1i(Get_Uniform_Location(name), value);
}
void Shader::Set_Uniform_Float(const std::string &name, float value) const
{
    glUniform1f(Get_Uniform_Location(name), value);
}
void Shader::Set_Uniform_3Float(const std::string &name, float x, float y, float z) const
{
    glUniform3f(Get_Uniform_Location(name), x, y, z);
}
void Shader::Set_Uniform_4Float(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(Get_Uniform_Location(name), x, y, z, w);
}
void Shader::Set_Uniform_4FMatrix(const std::string &name, glm::mat4 mvp) const
{
    glUniformMatrix4fv(Get_Uniform_Location(name), 1, GL_FALSE, glm::value_ptr(mvp));
}

int Shader::Get_Uniform_Location(const std::string &name) const
{
    if (_uniform_location_cash.find(name) != _uniform_location_cash.end())
        return _uniform_location_cash[name];

    int location = glGetUniformLocation(_id, name.c_str());

    if (location == -1)
    {
        // [...] OpenGL deletes your uniforms if they are not being used
        std::cout << "Can not find uniform: " << location;
    }
    _uniform_location_cash[name] = location;

    return location;
}