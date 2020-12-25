#if defined(DEBUG) && !defined(__ANDROID__)

#ifndef _WORLD_EDITOR_H_
#define _WORLD_EDITOR_H_

namespace sre
{
	
class SceneManager;
	
class WorldEditor
{
private:
	SceneManager* sceneManager;
	
private:
	void init(SceneManager* sceneManager);
	void XXX_MessageMethod(void* message);
	
	void onGUI(bool* enabled) const;

	void drawMenu(bool* enabled) const;

	void drawEntitiesWindow() const;
	void drawSceneTreeWindow() const;
	void drawEntityTree(class Entity* entity, int index) const;
	void drawPropertiesWindow() const;
	void drawMediaWindow() const;

friend class RenderEngine;
};

} // namespace

#endif
#endif