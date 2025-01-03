#ifndef _MESH_H_
#define _MESH_H_

#include "AEntityComponent.h"
#include "memory_aliases.h"
#include "Mesh.h"
#include "Material.h"

namespace sre
{

class Material;

class SRE_API MeshComponent : public AEntityComponent
{
DECLARE_COMPONENT()

protected:
    Mesh* mesh;

private:
    bool opaque;
    Material* material;

public:
    MeshComponent(Entity *entity);
    ~MeshComponent();

    Material *getMaterial();

    template <typename T, typename... TArgs>
    T *addMaterialComponent(TArgs&&... mArgs)
    {
        T * result = this->material->addComponent<T>(std::forward<TArgs>(mArgs)...);
        return result;
    }

    void setIsOpaque(bool value);

protected:
    bool isAbleToBeRendered();
    bool isOpaque();
    void load(const char* file);

friend class RenderManager;
friend class Entity;
friend class OpenGLAPI;
friend class OpenGLESAPI;
friend class MeshRenderer;
friend class ShadowRenderer;
friend class LightManager;
friend class Scene;
};

} // namespace

#endif
