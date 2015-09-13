#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <engine/nodes/renderables/materials/Material.h>
#include "VertexData.h"

namespace graphics
{
    class RenderManager;
}

namespace nodes
{

using namespace graphics;

/*!
	Class which holds information for rendering.
*/
class Mesh
{
    private:
        RenderManager *renderManager;

        void applyMaterial(bool receiveLight);

	protected:
        std::vector<VertexData> *vertexData;
        std::vector<unsigned int> *indices;
        Material *material;

        unsigned int vbo;
        unsigned int indexBO;
        int vertexAttribLocation;
        int normalAttribLocation;

	public:
        Mesh(std::vector<VertexData> *vertexData, std::vector<unsigned int> *indices);
		~Mesh();

        void setMaterial(Material *material);

    friend class ::graphics::RenderManager;
};

} // namespace nodes

#endif
