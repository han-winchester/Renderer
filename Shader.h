/* Modified from original source, created by Joey de Vries at learnopengl.com*/
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID{};

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);

    // activate the shader
    // ------------------------------------------------------------------------
    void use();

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;

    void setInt(const std::string& name, int value) const;

    void setFloat(const std::string& name, float value) const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;

    void setVec3(const std::string& name, float x, float y, float z) const;


private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif