#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <engine/utils/singleton_macros.h>
#include <engine/entities/renderables/meshes/VertexData.h>
#include "TextureManager.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include "MatrixManager.h"
#include <vector>

namespace sre
{

class Mesh;
class RenderableNode;
class LightNode;
class AGraphicsWrapper;
class Material;
class DiffuseMaterial;
class SceneManager;

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
        MatrixManager *matrixManager;
		AGraphicsWrapper *graphicsWrapper;

		void createBufferObject(Mesh *mesh);
		DirectionalLight *addDirectionalLight();
		PointLight *addPointLight();
		void render(const std::vector<RenderableNode *> &renderableNodes);

	public:
		static void DEBUG_drawTriangle();
		void clearBuffer();

		void applyMaterial(Material *material, bool receiveLight);
		void applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight);
		void drawMesh(Mesh *mesh);
		void releaseMaterial(Material *material);

		void renderCamera(Vector position, Vector lookTarget, Vector up);

		Texture *loadTexture(const std::string &fileName);
		unsigned int loadShader(const std::string &vertFile, const std::string &fragFile);

    friend class SceneManager;
    friend class Mesh;
};

} // namespace
#endif
