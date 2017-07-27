#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include <engine/entities/Entity.h>
#include <engine/entities/components/gui/GUITextComponent.h>
#include <map>

namespace sre
{

class GUIManager
{
private:
	std::map<std::string, UPTR<Entity>> entities;	// ### MUDAR PRA UNORDERED?
	uint32_t EntityIndex;

public:
	Entity *createGUIImageEntity(const std::string &fileName);
	Entity *createGUITextEntity(const std::string fontFile);
	void addEntity(Entity *entity, const std::string &name = "");

	~GUIManager();

private:
	GUIManager();
	const std::string generateEntityId();

friend class RenderEngine;
};

} // namespace

#endif
