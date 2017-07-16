#ifndef _GUI_TEXT_COMPONENT_H_
#define _GUI_TEXT_COMPONENT_H_

#include <engine/entities/components/AEntityComponent.h>
#include <engine/utils/memory_aliases.h>
#include <engine/entities/components/meshes/VertexData.h>

namespace sre
{

class Texture;

class GUITextComponent : public AEntityComponent
{
private:
	std::string fontFile;

private:
	GUITextComponent(Entity *entity, const std::string &fontFile);

friend class GUIManager;
friend class Entity;
};

} // namespace

#endif
