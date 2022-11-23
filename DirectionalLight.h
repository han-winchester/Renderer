#pragma once
#include "Light.h"
#include "Shader.h"
#include "glm/glm.hpp"
class DirectionalLight :
    public Light
{
public:
    DirectionalLight( glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, const Shader& shader);
    void SetDirection(glm::vec3 direction);
    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);
    void SetShader(const Shader& shader);
    void EnableDirectionalLight(bool enableDirectionalLight);

private:
    glm::vec3 m_Direction;
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    Shader m_Shader;
    bool m_EnableDirectionalLight;
};

