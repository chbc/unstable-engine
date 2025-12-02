#pragma once

#include "ABaseRenderer.h"

#include "ColorRendererComponent.h"
#include "EComponentId.h"
#include "memory_aliases.h"

#include <glm/vec3.hpp>
#include <list>
#include <vector>
#include <unordered_map>
#include <bitset>

namespace sre
{

class ABaseMaterial;
class AGraphicsWrapper;
class ShaderManager;

class MeshRenderer : public ABaseRenderer
{
private:
    std::unordered_map<size_t, UPTR<ColorRendererComponent>> componentsMap;
    std::unordered_map<std::string, UPTR<class BaseRendererShaderSetup>> shaderSetupItems;
    std::bitset<EComponentId::SIZE> componentsBitset;

public:
    virtual ~MeshRenderer();

private:
	MeshRenderer(ABaseMaterial* material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    template <typename T, typename... TArgs> T* addComponent(TArgs&&... mArgs);
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();
    template <typename T> size_t getComponentId();

    void init(bool useBrightnessSegmentation, bool includeDepth);
    void loadShaderSetupItems();
    void loadShader(bool useBrightnessSegmentation, bool includeDepth);
    void render();

friend class RenderManager;
};

} // namespace

#include "MeshRenderer.tpp"
