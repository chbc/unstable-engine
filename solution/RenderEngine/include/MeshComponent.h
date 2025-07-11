#pragma once

#include "memory_aliases.h"
#include "Model.h"
#include "ARenderableComponent.h"
#include "EDrawMode.h"

namespace sre
{

class ABaseMaterial;

class SRE_API MeshComponent : public ARenderableComponent
{
DECLARE_COMPONENT()

protected:
    MeshData* mesh{ nullptr };
    std::string modelPath;
    std::string meshName;

private:
    bool opaque{ true };
    ABaseMaterial* material{ nullptr };
    bool wireframe{ false };

public:
    MeshComponent(Entity *entity);
    ~MeshComponent();

    ABaseMaterial* getMaterial();

    /* XXX
    template <typename T, typename... TArgs>
    T *addMaterialComponent(TArgs&&... mArgs)
    {
        T * result = this->material->addComponent<T>(std::forward<TArgs>(mArgs)...);
        return result;
    }
    */

    void setIsOpaque(bool value);
    void setWireframeMode(bool value);
    EDrawMode::Type getDrawMode();
    void loadMaterial(const char* filePath);
    bool isMaterialStandard();

protected:
    bool isOpaque();
    void load(Model* model, const char* meshName);
    void onPropertyDeserialized() override;
    void onPropertyChanged() override;

private:
    void setMaterial(ABaseMaterial* arg_material);
    void refreshMesh();

friend class RenderManager;
friend class Entity;
friend class OpenGLAPI;
friend class OpenGLESAPI;
friend class ABaseRenderer;
friend class MeshRenderer;
friend class CustomRenderer;
friend class ShadowRenderer;
friend class LightManager;
friend class Scene;
};

} // namespace
