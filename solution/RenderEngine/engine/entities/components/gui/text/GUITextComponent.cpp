#include "GUITextComponent.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/systems/multimedia/textures/Texture.h>

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity, const std::string &fontFile)
	: AEntityComponent(entity)
{

}

} // namespace
