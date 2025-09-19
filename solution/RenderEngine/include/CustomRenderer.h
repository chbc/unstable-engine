#pragma once

#include "ABaseRenderer.h"
#include "EShaderComponent.h"

#include <string>
#include <unordered_map>

namespace sre
{

class AGraphicsWrapper;
class ShaderManager;
class CameraComponent;
class ABaseMaterial;

class CustomRenderer : public ABaseRenderer
{
private:
	std::unordered_map<EShaderComponent::Type, const std::string> shaderPaths;
	ABaseMaterial* material{ nullptr };

private:
	CustomRenderer(ABaseMaterial* arg_material, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWeapper);
	void init();
	void render(CameraComponent* camera);

friend class RenderManager;
};

} // namespace
