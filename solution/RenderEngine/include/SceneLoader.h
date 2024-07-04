#pragma once

namespace sre
{

class Scene;

class SceneLoader
{
private:
	static void load(Scene* scene);
	static void save(Scene* scene);

friend class EditorMenuBar;
friend class ScenesManager;
};

} // namespace
