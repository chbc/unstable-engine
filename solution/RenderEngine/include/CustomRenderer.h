#pragma once

#include "ABaseRenderer.h"

#include <string>

namespace sre
{

class AGraphicsWrapper;
class ShaderManager;
class CameraComponent;

class CustomRenderer : public ABaseRenderer
{
private:
	std::string shaderPath;

private:
	CustomRenderer(const std::string& arg_shaderPath, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWeapper);
	void init();
	void render(CameraComponent* camera);

friend class RenderManager;
};

} // namespace
