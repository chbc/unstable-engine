#ifndef _RENDERABLE_NODE_H_
#define _RENDERABLE_NODE_H_

#include <engine/nodes/Node.h>
#include "meshes/Mesh.h"

namespace sre
{

class RenderManager;
class SceneManager;

/*!
	Base class that represents a renderable node of a scene.
*/
class RenderableNode : public Node
{
	private:
		bool receiveLight;

	protected:
        RenderManager *renderManager;
        std::vector<Mesh *> meshes;

		RenderableNode();
        virtual ~RenderableNode();

	public:
        void setMaterial(Material *material, unsigned int meshIndex = 0);
		void setReceiveLight(bool receiveLight);

    friend class RenderManager;
    friend class SceneManager;
};

} // namespace

#endif
