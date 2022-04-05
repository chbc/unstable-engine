#ifndef _GUI_TEXT_COMPONENT_H_
#define _GUI_TEXT_COMPONENT_H_

#include "GUIImageComponent.h"
#include "PrimitiveMeshFactory.h"
#include "memory_aliases.h"
#include <string>

namespace sre
{


class FontAtlas;

class GUITextComponent : public GUIImageComponent
{
DECLARE_COMPONENT()

private:
	FontAtlas *atlas;

public:
    void onStart() override;
	SRE_API void setText(const std::string &text);

private:
	GUITextComponent(Entity *entity, uint32_t arg_maxItems);

	void loadFont(const std::string &fontFile);
	uint32_t getTextureId() override;

friend class GUIScene;
friend class Entity;
};

} // namespace

#endif
