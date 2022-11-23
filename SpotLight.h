#pragma once
#include "Light.h"
#include "Shader.h"
#include "glm/glm.hpp"
class SpotLight :
    public Light
{
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff, const Shader& shader);
    void SetPosition(glm::vec3 position);
    void SetDirection(glm::vec3 direction);
    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);
    void SetConstant(float constant);
    void SetLinear(float linear);
    void SetQuadratic(float quadratic);
    void SetCutOff(float cutOff);
    void SetOuterCutOff(float outerCutOff);
    void SetShader(const Shader& shader);
    void EnableSpotLight(bool enableSpotLight);

private:
    glm::vec3 m_Position;
    glm::vec3 m_Direction;
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    float m_Constant;
    float m_Linear;
    float m_Quadratic;
    float m_CutOff;
    float m_OuterCutOff;
    Shader m_Shader;
    bool m_EnableSpotLight;
};

