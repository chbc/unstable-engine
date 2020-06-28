#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "AComponentsHolder.h"
#include "LitRendererComponent.h"
#include "DiffuseRendererComponent.h"
#include "NormalRendererComponent.h"
#include "SpecularRendererComponent.h"
#include "AORendererComponent.h"
#include "OutlineRendererComponent.h"
#include <glm/vec3.hpp>
#include <list>
#include <unordered_map>
#include "ShaderLightData.h"

namespace sre
{

class MeshComponent;
class Material;
class MatrixManager;
class AGraphicsWrapper;
class ShaderManager;

class MeshRenderer : public AComponentsHolder<ColorRendererComponent>
{
private:
    std::unordered_map<std::string, UPTR<class BaseRendererShaderSetup>> shaderSetupItems;

    std::list<MeshComponent *> meshes;
    class Shader *shader;

    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

    ShaderLightData lightData;

public:
    virtual ~MeshRenderer();

private:
	MeshRenderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(bool useBrightnessSegmentation, bool includeDepth);
    void loadShaderSetupItems();
    void loadShader(bool useBrightnessSegmentation, bool includeDepth);

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

    void render(MatrixManager *matrixManager, const glm::vec3 &cameraPosition);

    bool contains(MeshComponent *mesh);
    bool fitsWithMesh(MeshComponent *mesh);
    inline bool isEmpty() { return this->meshes.empty(); }

    void removeDestroyedEntities();

    friend class RenderManager;
};

} // namespace

#endif
