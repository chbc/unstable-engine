#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <engine/util/singleton_macros.h>
#include <engine/math/Transform.h>
#include <engine/nodes/renderables/meshes/VertexData.h>
#include "TextureManager.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include <vector>

namespace nodes
{
    class Mesh;
    class RenderableNode;
    class LightNode;
}

class Material;
class DiffuseMaterial;
class SceneManager;

using namespace nodes;

namespace graphics
{

/*!
	Singleton Class for low level rendering
*/
class RenderManager
{
	DECLARE_SINGLETON(RenderManager);

	private:
		TextureManager *textureManager;
		ShaderManager *shaderManager;
		LightManager *lightManager;

		void createBufferObject(Mesh *mesh);
		DirectionalLight *addDirectionalLight();
		PointLight *addPointLight();
		void render(const std::vector<RenderableNode *> &renderableNodes);

	public:
		static void TEST_drawTriangle();
		void clearBuffer();

		void applyMaterial(Material *material, bool receiveLight);
		void applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight);
		void drawMesh(Mesh *mesh);
		void releaseMaterial(Material *material);

		void pushTransform(Transform *transform);
		void popTransform();

		void renderCamera(Vector position, Vector lookTarget, Vector up);

		Texture *loadTexture(const std::string &fileName);
		unsigned int loadShader(const std::string &vertFile, const std::string &fragFile);

    friend class ::SceneManager;
    friend class nodes::Mesh;
};

} // namespace graphics

#endif
