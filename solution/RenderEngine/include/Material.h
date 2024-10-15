#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "memory_aliases.h"

#include "AMaterialComponent.h"
#include "ColorMaterialComponent.h"
#include "LitMaterialComponent.h"
#include "DiffuseMaterialComponent.h"
#include "NormalMaterialComponent.h"
#include "SpecularMaterialComponent.h"
#include "AmbientOcclusionMaterialComponent.h"
#include "SpriteMaterialComponent.h"

#include "EComponentId.h"
#include <unordered_map>
#include <bitset>
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

namespace material
{
    template <typename T> SRE_API std::size_t getComponentId();
}

class Material
{
private:
    bool castShadow;
    std::unordered_map<size_t, UPTR<AMaterialComponent>> componentsMap;
    std::bitset<EComponentId::SIZE> componentsBitset;
    glm::vec2 uvOffset;
    glm::vec2 uvTiling;

public:
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

private:
    Material();

	template <typename T>
    std::size_t getComponentId()
	{
		return sre::material::getComponentId<T>();
	}

friend class MeshComponent;
friend class MeshRenderer;
friend class RenderManager;
friend class MaterialEditorProperty;
};

} // namespace

#include "Material.tpp"

#endif
