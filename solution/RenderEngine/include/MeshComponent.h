#pragma once

#include "AEntityComponent.h"
#include "memory_aliases.h"
#include "Model.h"
#include "Material.h"

namespace sre
{

class Material;

class SRE_API MeshComponent : public AEntityComponent
{
DECLARE_COMPONENT()

protected:
    MeshData* mesh;
    std::string modelPath;
    std::string meshName;

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
    bool isOpaque();
    void load(Model* model, const char* meshName);

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
