#pragma once

#include "ABaseMaterial.h"
#include "memory_aliases.h"
#include "core_defines.h"

#include <unordered_map>
#include <glm/glm.hpp>
#include "EComponentId.h"
#include <bitset>

namespace sre
{

class AMaterialComponent;

class Material : public ABaseMaterial
{
private:
    std::unordered_map<size_t, SPTR<AMaterialComponent>> componentsMap;
    std::bitset<EComponentId::SIZE> componentsBitset;
    glm::vec2 uvOffset{ 0.0f };
    glm::vec2 uvTiling{ 1.0f };
    bool castShadow{ false };

public:
    Material(std::string arg_filePath);
    template <typename T> T* addComponent();
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();

    AMaterialComponent* addComponent(const char* className);

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
friend class MaterialLoader;
};

} // namespace

#include "Material.tpp"
