#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <engine/entities/components/AComponentsHolder.h>
#include "ColorRendererComponent.h"
#include "DiffuseRendererComponent.h"
#include <glm/vec3.hpp>
#include <list>

namespace sre
{

class MeshComponent;
class Material;
class MatrixManager;
class AGraphicsWrapper;
class ShaderManager;
class LightManager;

class Renderer : public AComponentsHolder<ColorRendererComponent>
{
private:
	std::list<MeshComponent *> meshes;
	uint32_t shaderProgram;

	SPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

private:
	Renderer(Material *material, const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader();

	template <typename T, typename... TArgs>
	T *addComponent(TArgs&&... mArgs)
	{
		T *newComponent{ nullptr };

		if (!AComponentsHolder<ColorRendererComponent>::hasComponent<T>())
		{
			newComponent = new T{ std::forward<TArgs>(mArgs)... };
			AComponentsHolder<ColorRendererComponent>::addComponent(newComponent);
		}
		else
			throw "Can't add duplicate component!";

		return newComponent;
	}

	void addMesh(MeshComponent *mesh);
	void removeMesh(MeshComponent *mesh);

	void render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition);

	bool contains(MeshComponent *mesh);
	inline bool hasMeshes() { return this->meshes.size() > 0; }

	bool fitsWithMesh(MeshComponent *mesh);
	
	friend class RenderManager;
};

} // namespace

#endif
