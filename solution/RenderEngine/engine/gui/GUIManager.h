#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include <engine/entities/Entity.h>
#include <map>

namespace sre
{

class GUIManager
{
private:
	std::map<std::string, UPTR<Entity>> entities;
	uint32_t EntityIndex;

public:
	Entity *createGUIImageEntity(const std::string &fileName);
	void addEntity(Entity *entity, const std::string &name = "");

private:
	GUIManager();
	const std::string generateEntityId();

friend class RenderEngine;
};

} // namespace

#endif
