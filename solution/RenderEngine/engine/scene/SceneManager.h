#ifndef _SCENE_MANAGER_H//
#define _SCENE_MANAGER_H_

#include <engine/entities/CameraNode.h>
#include <engine/entities/renderables/RenderableNode.h>
#include <engine/entities/lights/DirectionalLight.h>
#include <engine/entities/lights/PointLight.h>
#include <engine/utils/singleton_macros.h>

namespace sre
{

class RenderEngine;

/*!
	Class for manager scene nodes.
*/
class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

	private:
		UPTR(CameraNode) mainCamera;

		std::vector<UPTR(RenderableNode)> renderableNodes;

		int nodeCount;

		int generateNodeId();
		void render();

	public:
		//Node *addNode();
		// renderables //
		RenderableNode *addCubeNode(float size = 1);
		RenderableNode *addPlaneNode(float size = 1);
		RenderableNode *addModelNode(const char *fileName);

		// light //
		DirectionalLight *addDirectionalLight();
		PointLight *addPointLight();

		// camera //
		CameraNode *getMainCamera();

	friend class Node;
	friend class RenderEngine;
};

} // namespace
#endif
