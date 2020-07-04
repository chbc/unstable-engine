#ifndef _WORLD_EDITOR_H_
#define _WORLD_EDITOR_H_

namespace sre
{
	
class WorldEditor
{
private:
	void onGUI(bool* enabled) const;

	void drawMenu(bool* enabled) const;

	void drawEntitiesWindow() const;
	void drawSceneTreeWindow() const;
	void drawPropertiesWindow() const;
	void drawMediaWindow() const;

friend class RenderEngine;
};

} // namespace

#endif
