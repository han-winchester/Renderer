#include "DirectionalLight.h"

std::vector<DirectionalLight> DirectionalLight::directionalLights;
int DirectionalLight::directionalLightCount = 0;

DirectionalLight::DirectionalLight( glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: m_Direction(direction),
	m_Ambient(ambient),
	m_Diffuse(diffuse),
	m_Specular(specular),
	m_EnableDirectionalLight(true)
{
	this->directionalLightID = directionalLightCount;
	directionalLights.push_back(*this);
	directionalLightCount += 1;
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	DirectionalLight::directionalLights[this->directionalLightID].m_Direction = direction;
}

void DirectionalLight::SetAmbient(glm::vec3 ambient)
{
	DirectionalLight::directionalLights[this->directionalLightID].m_Ambient = ambient;
}

void DirectionalLight::SetDiffuse(glm::vec3 diffuse)
{
	DirectionalLight::directionalLights[this->directionalLightID].m_Diffuse = diffuse;
}

void DirectionalLight::SetSpecular(glm::vec3 specular)
{
	DirectionalLight::directionalLights[this->directionalLightID].m_Specular = specular;
}


void DirectionalLight::EnableDirectionalLight(bool enableDirectionalLight)
{
	DirectionalLight::directionalLights[this->directionalLightID].m_EnableDirectionalLight = enableDirectionalLight;
}

void DirectionalLight::Draw(Shader& shader)
{
	shader.use();
	shader.setVec3(	"directionalLights[" + std::to_string(this->directionalLightID) + "].direction"		,m_Direction);
	shader.setVec3(	"directionalLights[" + std::to_string(this->directionalLightID) + "].ambient"		,m_Ambient);
	shader.setVec3(	"directionalLights[" + std::to_string(this->directionalLightID) + "].diffuse"		,m_Diffuse);
	shader.setVec3(	"directionalLights[" + std::to_string(this->directionalLightID) + "].specular"		,m_Specular);
	shader.setBool(	"directionalLightEnabled"															,m_EnableDirectionalLight);

}