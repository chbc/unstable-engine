#pragma once

namespace c4
{
	namespace yml
	{
		class NodeRef;
		class ConstNodeRef;
	}
}

namespace sre
{

class AScene;
class Entity;
struct ModifiedEntityData;

class SceneLoader
{
private:
	static void save(AScene* scene, const char* sceneName);
	static void serializeEntity(AScene* scene, c4::yml::NodeRef& entityNode, Entity* entity);
	static void serializeModifiedAssetProperties(AScene* scene, c4::yml::NodeRef& entityNode, Entity* entity);
	static void load(AScene* scene, const char* sceneName);

friend class EditorsController;
friend class ScenesManager;
friend class RenderEngine;
};

} // namespace
