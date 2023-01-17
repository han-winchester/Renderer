#pragma once
#include "../glm/glm.hpp"
#include "../Lights/DirectionalLight.h"
#include <imgui.h>


namespace RenderUI
{
	
    static bool renderPointLights{true};
    static bool enableDirectionalLight{true};
    static glm::vec3 directionalLightAmbient{};
	void RenderUI();



}

