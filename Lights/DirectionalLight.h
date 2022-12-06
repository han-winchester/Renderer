#pragma once
#include "../Shader.h"
#include "../glm/glm.hpp"
#include <vector>

class DirectionalLight
{
    static int directionalLightCount;
public:
    static std::vector<DirectionalLight> directionalLights;
    DirectionalLight( glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void SetDirection(glm::vec3 direction);
    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);
    void EnableDirectionalLight(bool enableDirectionalLight);
    void Draw(Shader& shader) const;

private:
    int directionalLightID;
    glm::vec3 m_Direction;
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    bool m_EnableDirectionalLight;
};

