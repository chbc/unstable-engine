#ifndef _MESH_H_
#define _MESH_H_

#include "../ARenderableComponent.h"
#include "materials/Material.h"

namespace sre
{

/*!
	Class that holds information for rendering.
*/
class MeshComponent : public ARenderableComponent<VertexData>
{
private:
    UPTR<Material> material;

    MeshComponent(Entity *entity, UPTR<MeshData<VertexData>> &meshData);

public:
    Material *getMaterial();
    void setMaterial(UPTR<Material> &material);

    template <typename T, typename... TArgs>
    T *addMaterialComponent(TArgs&&... mArgs)
    {
        T * result = this->material->addComponent<T>(std::forward<TArgs>(mArgs)...);
        return result;
    }

friend class RenderManager;
friend class Entity;
friend class OpenGLAPI;
friend class Renderer;
friend class VertexDataFactory;
friend class LightManager;
};

} // namespace

#endif
