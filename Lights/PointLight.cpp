#include "PointLight.h"

std::vector<PointLight> PointLight::pointLights;
int PointLight::lightPointCount{};

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
	: m_Position{position},
	m_Ambient{ambient},
	m_Diffuse{diffuse},
	m_Specular{specular},
	m_Constant{constant},
	m_Linear{linear},
	m_Quadratic{quadratic}
{
	
	this->lightPointID = lightPointCount;
	pointLights.push_back(*this);
	lightPointCount += 1;
}

void PointLight::SetPosition(glm::vec3 position)
{
	PointLight::pointLights[this->lightPointID].m_Position = position;
}

void PointLight::SetAmbient(glm::vec3 ambient)
{
	PointLight::pointLights[this->lightPointID].m_Ambient = ambient;
}

void PointLight::SetDiffuse(glm::vec3 diffuse)
{
	PointLight::pointLights[this->lightPointID].m_Diffuse = diffuse;
}

void PointLight::SetSpecular(glm::vec3 specular)
{
	PointLight::pointLights[this->lightPointID].m_Specular = specular;
}

void PointLight::SetConstant(float constant)
{
	PointLight::pointLights[this->lightPointID].m_Constant = constant;
}

void PointLight::SetLinear(float linear)
{
	PointLight::pointLights[this->lightPointID].m_Linear = linear;
}

void PointLight::SetQuadratic(float quadratic)
{
	PointLight::pointLights[this->lightPointID].m_Quadratic = quadratic;

}

void PointLight::Draw(Shader& shader) const
{
	shader.use();
	shader.setVec3(	"pointLights[" + std::to_string(this->lightPointID) + "].position"	,m_Position);
	shader.setVec3(	"pointLights[" + std::to_string(this->lightPointID) + "].ambient"	,m_Ambient);
	shader.setVec3(	"pointLights[" + std::to_string(this->lightPointID) + "].diffuse"	,m_Diffuse);
	shader.setVec3(	"pointLights[" + std::to_string(this->lightPointID) + "].specular"	,m_Specular);
	shader.setFloat("pointLights[" + std::to_string(this->lightPointID) + "].constant"	,m_Constant);
	shader.setFloat("pointLights[" + std::to_string(this->lightPointID) + "].linear"	,m_Linear);
	shader.setFloat("pointLights[" + std::to_string(this->lightPointID) + "].quadratic"	,m_Quadratic);
}
