#ifndef _SCENE_MANAGER_H//
#define _SCENE_MANAGER_H_

#include <engine/nodes/CameraNode.h>
#include <engine/nodes/renderables/RenderableNode.h>
#include <engine/nodes/lights/DirectionalLight.h>
#include <engine/nodes/lights/PointLight.h>
#include <engine/util/singleton_macros.h>

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
		CameraNode *mainCamera;

		std::vector<RenderableNode *> renderableNodes;

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
