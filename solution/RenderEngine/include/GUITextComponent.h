#pragma once

#include "ABaseGUIComponent.h"

#include <string>

namespace sre
{

class FontAtlas;

class GUITextComponent : public ABaseGUIComponent
{
DECLARE_COMPONENT()

private:
	FontAtlas* atlas{ nullptr };
	uint32_t maxItems{ 10 };
	bool isDynamic{ true };

public:
	GUITextComponent(Entity *entity);
	SRE_API void setText(const std::string &text);
	uint32_t getTextureId() override;

private:
	void setMaxItems(uint32_t arg_maxItems);
	inline bool getIsDynamic() { return this->isDynamic; }
	void load(const std::string &fontFile);

friend class GUIScene;
friend class GUIRenderer;
friend class Entity;
};

} // namespace
