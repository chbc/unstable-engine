#pragma once

#include "CustomRenderer.h"

namespace sre
{

class SkyboxComponent;
class ABaseMaterial;

class SkyboxRenderer : public CustomRenderer
{
private:
	SkyboxRenderer(ABaseMaterial* arg_material, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWeapper);
	void init() override;
	void initTextures() override;
	void render(CameraComponent* camera) override;
	void setupTextures() override;
	void reloadMaterial(ABaseMaterial* newMaterial);

friend class RenderManager;
};

} // namespace
