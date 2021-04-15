#ifndef _MESH_H_
#define _MESH_H_

#include "ARenderableComponent.h"
#include "Material.h"

namespace sre
{

/*!
	Class that holds information for rendering.
*/
class SRE_API MeshComponent : public ARenderableComponent
{
DECLARE_COMPONENT()

private:
    UPTR<Material> material;

    MeshComponent(Entity *entity, MeshData* meshData);

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
friend class OpenGLESAPI;
friend class MeshRenderer;
friend class ShadowRenderer;
friend class VertexDataFactory;
friend class LightManager;
};

} // namespace

#endif
