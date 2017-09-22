#ifndef _GUI_TEXT_COMPONENT_H_
#define _GUI_TEXT_COMPONENT_H_

#include "GUIImageComponent.h"
#include <engine/systems/graphics/meshData/PrimitiveMeshFactory.h>
#include <engine/utils/memory_aliases.h>
#include <string>

namespace sre
{

class Atlas;

class GUITextComponent : public GUIImageComponent
{
private:
	Atlas *atlas;

public:
	void setText(const std::string &text);

private:
	GUITextComponent(Entity *entity);

	void loadFont(const std::string &fontFile);
	void makeGliph(int id);
	uint32_t getTextureId() override;

friend class GUIManager;
friend class Entity;
};

} // namespace

#endif
