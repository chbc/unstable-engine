#pragma once

#include "DiffuseRendererComponent.h"

namespace sre
{

class SpriteRendererComponent : public DiffuseRendererComponent
{
protected:
	SpriteRendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper);
	
	void setupShaderValues(MeshComponent* mesh, uint32_t program) override;

friend class MeshRenderer;
};
	
} // sre
