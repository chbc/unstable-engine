#pragma once

#include <list>


namespace sre
{

class AGraphicsWrapper;
class ShaderManager;
class MeshComponent;

class ABaseRenderer
{
protected:
	AGraphicsWrapper* graphicsWrapper{ nullptr };
	ShaderManager* shaderManager{ nullptr };
	uint32_t program{ 0 };
	std::list<MeshComponent*> meshComponents;

public:
	inline bool isEmpty() { return this->meshComponents.empty(); }

protected:
	ABaseRenderer(ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWrapper);
	virtual ~ABaseRenderer() = default;

	void addMesh(MeshComponent* meshComponent);
	void removeDestroyedEntities();
	bool removeMesh(MeshComponent* mesh);

friend class RenderManager;
};

} // namespace
