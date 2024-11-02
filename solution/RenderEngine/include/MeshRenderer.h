#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include <glm/vec3.hpp>
#include <list>
#include <unordered_map>
#include <bitset>
#include "ColorRendererComponent.h"
#include "ShaderLightData.h"
#include "EComponentId.h"
#include "memory_aliases.h"

namespace sre
{

class MeshComponent;
class Material;
class AGraphicsWrapper;
class ShaderManager;

class MeshRenderer
{
private:
    std::unordered_map<int, UPTR<ColorRendererComponent>> componentsMap;
    std::unordered_map<std::string, UPTR<class BaseRendererShaderSetup>> shaderSetupItems;
    std::bitset<EComponentId::SIZE> componentsBitset;

    std::list<MeshComponent *> meshes;
    class Shader *shader;

    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

    ShaderLightData lightData;

public:
    virtual ~MeshRenderer();
    inline bool isEmpty() { return this->meshes.empty(); }

private:
	MeshRenderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    template <typename T, typename... TArgs> T* addComponent(TArgs&&... mArgs);
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();
    template <typename T> int getComponentId();

    void onSceneLoaded(bool useBrightnessSegmentation, bool includeDepth);
    void loadShaderSetupItems();
    void loadShader(bool useBrightnessSegmentation, bool includeDepth);
    
    void addMesh(MeshComponent *mesh);

    void render(const glm::vec3 &cameraPosition);

    bool contains(MeshComponent *mesh);
    bool fitsWithMesh(MeshComponent *mesh);

    void removeDestroyedEntities();
    void clean();

    friend class RenderManager;
};

} // namespace

#include "MeshRenderer.tpp"

#endif
