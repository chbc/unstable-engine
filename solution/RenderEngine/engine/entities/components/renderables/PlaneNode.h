#ifndef _PLANE_NODE_H_
#define _PLANE_NODE_H_

#include "RenderableNode.h"

class SceneManager;

namespace sre
{

class PlaneNode : public RenderableNode
{
	private:
		PlaneNode(float size = 1);

	friend class SceneManager;
};

} // namespace
#endif
