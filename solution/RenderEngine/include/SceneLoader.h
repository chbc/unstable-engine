#pragma once

namespace sre
{

class AScene;

class SceneLoader
{
private:
	static void save(AScene* scene, const char* sceneName);
	static void load(AScene* scene, const char* sceneName);

friend class EditorsController;
friend class ScenesManager;
friend class RenderEngine;
};

} // namespace
