#pragma once

#include "memory_aliases.h"
#include "Model.h"
#include "Material.h"
#include "ARenderableComponent.h"

namespace sre
{

class Material;

class SRE_API MeshComponent : public ARenderableComponent
{
DECLARE_COMPONENT()

protected:
    MeshData* mesh{ nullptr };
    std::string modelPath;
    std::string meshName;

private:
    bool opaque{ true };
    Material* material{ nullptr };

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
    void onPropertyDeserialized() override;
    void onPropertyChanged() override;

private:
    void setMaterial(Material* arg_material);

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
