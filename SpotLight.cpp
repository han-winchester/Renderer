#include "SpotLight.h"

std::vector<SpotLight> SpotLight::spotLights;
int SpotLight::spotLightCount = 0;

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
	: m_Position(position),
	m_Direction(direction),
	m_Ambient(ambient),
	m_Diffuse(diffuse),
	m_Specular(specular),
	m_Constant(constant),
	m_Linear(linear),
	m_Quadratic(quadratic),
	m_CutOff(cutOff),
	m_OuterCutOff(outerCutOff),
	m_EnableSpotLight(true)
{
	this->spotLightID = spotLightCount;
	spotLights.push_back(*this);
	spotLightCount += 1;
}

void SpotLight::SetPosition(glm::vec3 position)
{
	SpotLight::spotLights[this->spotLightID].m_Position = position;
}

void SpotLight::SetDirection(glm::vec3 direction)
{
	SpotLight::spotLights[this->spotLightID].m_Direction = direction;
}

void SpotLight::SetAmbient(glm::vec3 ambient)
{
	SpotLight::spotLights[this->spotLightID].m_Ambient = ambient;
}

void SpotLight::SetDiffuse(glm::vec3 diffuse)
{
	SpotLight::spotLights[this->spotLightID].m_Diffuse = diffuse;
}

void SpotLight::SetSpecular(glm::vec3 specular)
{
	SpotLight::spotLights[this->spotLightID].m_Specular = specular;
}

void SpotLight::SetConstant(float constant)
{
	SpotLight::spotLights[this->spotLightID].m_Constant = constant;
}

void SpotLight::SetLinear(float linear)
{
	SpotLight::spotLights[this->spotLightID].m_Linear = linear;
}

void SpotLight::SetQuadratic(float quadratic)
{
	SpotLight::spotLights[this->spotLightID].m_Quadratic = quadratic;
}

void SpotLight::SetCutOff(float cutOff)
{
	SpotLight::spotLights[this->spotLightID].m_CutOff = cutOff;
}

void SpotLight::SetOuterCutOff(float outerCutOff)
{
	SpotLight::spotLights[this->spotLightID].m_OuterCutOff = outerCutOff;
}

void SpotLight::EnableSpotLight(bool enableSpotLight)
{
	SpotLight::spotLights[this->spotLightID].m_EnableSpotLight = enableSpotLight;
}

void SpotLight::Draw(Shader& shader)
{
	shader.use();
	shader.setVec3(	"spotLights[" + std::to_string(this->spotLightID) + "].position"			,m_Position);
	shader.setVec3(	"spotLights[" + std::to_string(this->spotLightID) + "].direction"			,m_Direction);
	shader.setVec3(	"spotLights[" + std::to_string(this->spotLightID) + "].ambient"				,m_Ambient);
	shader.setVec3(	"spotLights[" + std::to_string(this->spotLightID) + "].diffuse"				,m_Diffuse);
	shader.setVec3(	"spotLights[" + std::to_string(this->spotLightID) + "].specular"			,m_Specular);
	shader.setFloat("spotLights[" + std::to_string(this->spotLightID) + "].constant"			,m_Constant);
	shader.setFloat("spotLights[" + std::to_string(this->spotLightID) + "].linear"				,m_Linear);
	shader.setFloat("spotLights[" + std::to_string(this->spotLightID) + "].quadratic"			,m_Quadratic);
	shader.setFloat("spotLights[" + std::to_string(this->spotLightID) + "].cutOff"				,m_CutOff);
	shader.setFloat("spotLights[" + std::to_string(this->spotLightID) + "].outerCutOff"			,m_OuterCutOff);
	shader.setBool(	"spotLightEnabled"															,m_EnableSpotLight);

}
