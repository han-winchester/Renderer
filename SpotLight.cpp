#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff, const Shader& shader)
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
	m_Shader(shader),
	m_EnableSpotLight(true)
{
	    m_Shader.setVec3("spotLight.position", m_Position);
        m_Shader.setVec3("spotLight.direction", m_Direction);
        m_Shader.setVec3("spotLight.ambient", m_Ambient);
        m_Shader.setVec3("spotLight.diffuse", m_Diffuse);
        m_Shader.setVec3("spotLight.specular", m_Specular);
        m_Shader.setFloat("spotLight.constant", m_Constant);
        m_Shader.setFloat("spotLight.linear", m_Linear);
        m_Shader.setFloat("spotLight.quadratic", m_Quadratic);
        m_Shader.setFloat("spotLight.cutOff", m_CutOff);
        m_Shader.setFloat("spotLight.outerCutOff", m_OuterCutOff);
		m_Shader.setBool("spotLightEnabled", m_EnableSpotLight);
}

void SpotLight::SetPosition(glm::vec3 position)
{
	m_Position = position;
	m_Shader.setVec3("spotLight.position", m_Position);
}

void SpotLight::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
	m_Shader.setVec3("spotLight.direction", m_Direction);
}

void SpotLight::SetAmbient(glm::vec3 ambient)
{
	m_Ambient = ambient;
	m_Shader.setVec3("spotLight.ambient", m_Ambient);
}

void SpotLight::SetDiffuse(glm::vec3 diffuse)
{
	m_Diffuse = diffuse;
	m_Shader.setVec3("spotLight.diffuse", m_Diffuse);
}

void SpotLight::SetSpecular(glm::vec3 specular)
{
	m_Specular = specular;
	m_Shader.setVec3("spotLight.specular", m_Specular);
}

void SpotLight::SetConstant(float constant)
{
	m_Constant = constant;
	m_Shader.setFloat("spotLight.constant", m_Constant);
}

void SpotLight::SetLinear(float linear)
{
	m_Linear = linear;
	m_Shader.setFloat("spotLight.linear", m_Linear);
}

void SpotLight::SetQuadratic(float quadratic)
{
	m_Quadratic = quadratic;
	m_Shader.setFloat("spotLight.quadratic", m_Quadratic);
}

void SpotLight::SetCutOff(float cutOff)
{
	m_CutOff = cutOff;
	m_Shader.setFloat("spotLight.cutOff", m_CutOff);
}

void SpotLight::SetOuterCutOff(float outerCutOff)
{
	m_OuterCutOff = outerCutOff;
	m_Shader.setFloat("spotLight.outerCutOff", m_OuterCutOff);
}

void SpotLight::SetShader(const Shader& shader)
{
	m_Shader = shader;
	// TODO: Need to call all the setters above again?
}

void SpotLight::EnableSpotLight(bool enableSpotLight)
{
	m_EnableSpotLight = enableSpotLight;
	m_Shader.setBool("spotLightEnabled", m_EnableSpotLight);
}
