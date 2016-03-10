#ifndef _CAMERA_NODE_H_
#define _CAMERA_NODE_H_

#include "Node.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

class SceneManager;

/*!
	Class that handles the camera on the scene.
*/
class CameraNode : public Node
{
	private:
		Vector lookTarget;
		Vector up;

		CameraNode();

	public:
		void setLookAt(const Vector &target);

	friend class SceneManager;
};

} // namespace

#endif
