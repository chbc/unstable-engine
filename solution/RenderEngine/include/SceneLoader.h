#pragma once

namespace sre
{

class Scene;

class SceneLoader
{
private:
	static void save(Scene* scene);
	static void load(Scene* scene, const char* sceneName);

friend class EditorMenuBar;
friend class ScenesManager;
friend class RenderEngine;
};

} // namespace
