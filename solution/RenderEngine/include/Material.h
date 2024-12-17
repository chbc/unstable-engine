#pragma once

#include "memory_aliases.h"
#include "core_defines.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include <string>
#include "EComponentId.h"
#include <bitset>

namespace sre
{

class AMaterialComponent;

class Material
{
private:
    std::string fileName{ "DefaultMaterial.mat" };
    std::unordered_map<size_t, SPTR<AMaterialComponent>> componentsMap;
    std::bitset<EComponentId::SIZE> componentsBitset;
    glm::vec2 uvOffset;
    glm::vec2 uvTiling;
    bool castShadow;

private:
    Material();

public:
    AMaterialComponent* addComponent(const char* className);
    template <typename T, typename... TArgs> T* addComponent(TArgs&&... mArgs);
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();

	SRE_API void setCastShadow(bool value);
	SRE_API void setReceivesLight(bool value);
	SRE_API bool getReceivesLight();
    SRE_API void setUVOffset(glm::vec2 uvOffset);
    SRE_API void setUVTiling(glm::vec2 tiling);
    SRE_API glm::vec2 getUVOffset();
    SRE_API glm::vec2 getUVTiling();

friend class MeshComponent;
friend class MeshRenderer;
friend class RenderManager;
friend class MaterialEditorProperty;
};

} // namespace

#include "Material.tpp"
