#ifndef _GUI_TEXT_COMPONENT_H_
#define _GUI_TEXT_COMPONENT_H_

#include <engine/entities/components/AEntityComponent.h>
#include <engine/entities/components/meshes/VertexData.h>
#include <string>

namespace sre
{

class Atlas;

class GUITextComponent : public AEntityComponent
{
private:
	Atlas *atlas;

private:
	GUITextComponent(Entity *entity);

	void loadFont(const std::string &fontFile);

public:
	void setText(const std::string &text);

friend class GUIManager;
friend class Entity;
};

} // namespace

#endif
