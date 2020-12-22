#ifndef _SPRITE_RENDERER_COMPONENT_H_
#define _SPRITE_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class SpriteRendererComponent : public DiffuseRendererComponent
{
protected:
	SpriteRendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper);
	
	void setupShaderValues(MeshComponent* mesh, Shader* shader) override;

friend class MeshRenderer;
};
	
} // sre

#endif
