#pragma once

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    unsigned int _id;
    int  _success;
    char _infoLog[512];
    mutable std::unordered_map<std::string, int> _uniform_location_cash;

    std::string Load_Shader(const char *filename);
    unsigned int Compile_Shader(unsigned int type, const std::string &source);
    int Get_Uniform_Location(const std::string &name) const;

public:
    // [...] constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);
    // [...] activate/di-activate the shader
    void Bind() const;
    void UnBind() const;
    // utility uniform functions
    void Set_Uniform_Bool(const std::string &name, bool value) const;
    void Set_Uniform_Int(const std::string &name, int value) const;
    void Set_Uniform_Float(const std::string &name, float value) const;
    void Set_Uniform_4Float(const std::string &name, float x, float y, float z, float w) const;
    void Set_Uniform_4FMatrix(const std::string &name, glm::mat4 mvp) const;
};