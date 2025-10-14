#pragma once

#include "CustomRenderer.h"

namespace sre
{

class SkyboxComponent;

class SkyboxRenderer : public CustomRenderer
{
private:
	SkyboxRenderer(class ABaseMaterial* arg_material, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWeapper);
	void init() override;
	void initTextures() override;
	void render(CameraComponent* camera) override;
	void setupTextures() override;

friend class RenderManager;
};

} // namespace
