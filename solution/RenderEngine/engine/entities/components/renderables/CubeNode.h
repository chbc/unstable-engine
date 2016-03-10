#ifndef _CUBE_NODE_H_
#define _CUBE_NODE_H_

#include "RenderableNode.h"

class SceneManager;

namespace sre
{

/*!
	Class that represents a cube as a scene node.
*/
class CubeNode : public RenderableNode
{
	private:
		CubeNode(float size = 1);

	friend class SceneManager;
};

} // namespace

#endif
