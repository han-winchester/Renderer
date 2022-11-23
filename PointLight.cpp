#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, const Shader& shader)
	: m_Position(position),
	m_Ambient(ambient),
	m_Diffuse(diffuse),
	m_Specular(specular),
	m_Constant(constant),
	m_Linear(linear),
	m_Quadratic(quadratic),
	m_Shader(shader),
	m_EnablePointLight(true)

{
}

void PointLight::SetPosition(glm::vec3 position)
{
	m_Position = position;
}

void PointLight::SetAmbient(glm::vec3 ambient)
{
	m_Ambient = ambient;
}

void PointLight::SetDiffuse(glm::vec3 diffuse)
{
	m_Diffuse = diffuse;
}

void PointLight::SetSpecular(glm::vec3 specular)
{
	m_Specular = specular;
}

void PointLight::SetConstant(float constant)
{
	m_Constant = constant;
}

void PointLight::SetLinear(float linear)
{
	m_Linear = linear;
}

void PointLight::SetQuadratic(float quadratic)
{
	m_Quadratic = quadratic;

}

void PointLight::SetShader(const Shader& shader)
{
	m_Shader = shader;
	// TODO: Need to call all the setters above again?
}

void PointLight::EnablePointLight(bool enablePointLight)
{
	m_EnablePointLight = enablePointLight;
	m_Shader.setBool("enablePointLight", m_EnablePointLight);
}
