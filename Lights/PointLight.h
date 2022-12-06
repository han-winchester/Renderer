#pragma once
#include "../Camera.h"
#include "../Shader.h"
#include "../glm/glm.hpp"
#include <vector>
class PointLight
{
    static int lightPointCount;
public:
    static std::vector<PointLight> pointLights;
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    void SetPosition(glm::vec3 position);
    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);
    void SetConstant(float constant);
    void SetLinear(float linear);
    void SetQuadratic(float quadratic);
    void Draw(Shader& shader);

private:
    int lightPointID;
    glm::vec3 m_Position;
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    float m_Constant;
    float m_Linear;
    float m_Quadratic;
};

