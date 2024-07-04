#include "Material.h"

namespace sre
{

Material::Material() : castShadow(false)
{
    this->addComponent<ColorMaterialComponent>();
}

void Material::setCastShadow(bool value)
{
	this->castShadow = value;
}

void Material::setReceivesLight(bool value)
{
    bool hasLit = this->hasComponent<LitMaterialComponent>();
    if (value && !hasLit)
        this->addComponent<LitMaterialComponent>();
    else if (!value && hasLit)
        this->removeComponent<LitMaterialComponent>();
}

bool Material::getReceivesLight()
{
    return this->hasComponent<LitMaterialComponent>();
}

namespace material
{
    template <typename T> SRE_API std::size_t getComponentId();

    template <> std::size_t SRE_API getComponentId<ColorMaterialComponent>() { return EComponentId::COLOR_MATERIAL; }
    template <> std::size_t SRE_API getComponentId<LitMaterialComponent>() { return EComponentId::LIT_MATERIAL; }
    template <> std::size_t SRE_API getComponentId<DiffuseMaterialComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
    template <> std::size_t SRE_API getComponentId<NormalMaterialComponent>() { return EComponentId::NORMAL_MATERIAL; }
    template <> std::size_t SRE_API getComponentId<SpecularMaterialComponent>() { return EComponentId::SPECULAR_MATERIAL; }
    template <> std::size_t SRE_API getComponentId<AmbientOcclusionMaterialComponent>() { return EComponentId::AO_MATERIAL; }
    template <> std::size_t SRE_API getComponentId<SpriteMaterialComponent>() { return EComponentId::SPRITE_MATERIAL; }
} // namespace

} // namespace
