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
class CustomMaterial;
class Texture;

class CustomRenderer : public ABaseRenderer
{
protected:
	std::unordered_map<EShaderComponent::Type, const std::string> shaderPaths;
	CustomMaterial* material{ nullptr };
	std::unordered_map<std::string, Texture*> texturesMap;

protected:
	CustomRenderer(class ABaseMaterial* arg_material, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWeapper);
	virtual void init();
	virtual void initTextures();
	virtual void render(CameraComponent* camera);
	virtual void setupTextures();

friend class RenderManager;
};

} // namespace
