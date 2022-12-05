#include "DirectionalLight.h"

DirectionalLight::DirectionalLight( glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, const Shader& shader)
	: m_Direction(direction),
	m_Ambient(ambient),
	m_Diffuse(diffuse),
	m_Specular(specular),
	m_Shader(shader),
	m_EnableDirectionalLight(true)
{
	m_Shader.setVec3("dirLight.direction", m_Direction);
    m_Shader.setVec3("dirLight.ambient", m_Ambient);
    m_Shader.setVec3("dirLight.diffuse", m_Diffuse);
    m_Shader.setVec3("dirLight.specular", m_Specular);
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
	m_Shader.setVec3("dirLight.direction", m_Direction);
}

void DirectionalLight::SetAmbient(glm::vec3 ambient)
{
	m_Ambient = ambient;
	m_Shader.setVec3("dirLight.ambient", m_Ambient);
}

void DirectionalLight::SetDiffuse(glm::vec3 diffuse)
{
	m_Diffuse = diffuse;
	m_Shader.setVec3("dirLight.diffuse", m_Diffuse);
}

void DirectionalLight::SetSpecular(glm::vec3 specular)
{
	m_Specular = specular;
	m_Shader.setVec3("dirLight.specular", m_Specular);
}

void DirectionalLight::SetShader(const Shader& shader)
{
	m_Shader = shader;
	// TODO: Need to call all the setters above again?
}

void DirectionalLight::EnableDirectionalLight(bool enableDirectionalLight)
{
	m_EnableDirectionalLight = enableDirectionalLight;
	m_Shader.setBool("directionalLightEnabled", m_EnableDirectionalLight);
}
