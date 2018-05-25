#ifndef _GUI_TEXT_COMPONENT_H_
#define _GUI_TEXT_COMPONENT_H_

#include "GUIImageComponent.h"
#include <engine/core/graphics/meshData/PrimitiveMeshFactory.h>
#include <engine/utils/memory_aliases.h>
#include <string>

namespace sre
{

class FontAtlas;

class GUITextComponent : public GUIImageComponent
{
private:
	FontAtlas *atlas;

public:
    void onStart() override;
	void setText(const std::string &text);

private:
	GUITextComponent(Entity *entity, int maxItems);

	void loadFont(const std::string &fontFile);
	uint32_t getTextureId() override;

friend class GUIManager;
friend class Entity;
};

} // namespace

#endif
