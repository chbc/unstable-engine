#ifndef _A_COMPONENTS_HOLDER_H_
#define _A_COMPONENTS_HOLDER_H_

#include <engine/utils/memory_aliases.h>
#include <bitset>
#include <unordered_map>
#include "EComponentId.h"

namespace sre
{

constexpr size_t MAX_COMPONENTS{ 13 };

template <typename C>
class AComponentsHolder
{
protected:
    std::bitset<MAX_COMPONENTS> componentsBitset;
    std::unordered_map<size_t, UPTR<C>> componentsMap;

public:
    template <typename T> T *getComponent(); // throws "Can't find component"
    template <typename T> bool hasComponent();

protected:
    template <typename T> void addComponent(T *newComponent);
    template <typename T> void removeComponent();

private:
    template <typename T>
    std::size_t getComponentId();

    // Entity components
    template <> std::size_t getComponentId<class TransformComponent>() { return EComponentId::TRANSFORM; }
    template <> std::size_t getComponentId<class CameraComponent>() { return EComponentId::CAMERA; }
    template <> std::size_t getComponentId<class DirectionalLightComponent>() { return EComponentId::DIRECTIONAL_LIGHT; }
    template <> std::size_t getComponentId<class PointLightComponent>() { return EComponentId::POINT_LIGHT; }
    template <> std::size_t getComponentId<class MeshComponent>() { return EComponentId::MESH; }

    // Material components
    template <> std::size_t getComponentId<class ColorMaterialComponent>() { return EComponentId::COLOR_MATERIAL; }
    template <> std::size_t getComponentId<class LitMaterialComponent>() { return EComponentId::LIT_MATERIAL; }
    template <> std::size_t getComponentId<class DiffuseMaterialComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
    template <> std::size_t getComponentId<class NormalMaterialComponent>() { return EComponentId::NORMAL_MATERIAL; }
    template <> std::size_t getComponentId<class SpecularMaterialComponent>() { return EComponentId::SPECULAR_MATERIAL; }
    template <> std::size_t getComponentId<class AmbientOcclusionMaterialComponent>() { return EComponentId::AO_MATERIAL; }

    // GUI components
    template <> std::size_t getComponentId<class GUIImageComponent>() { return EComponentId::GUI_IMAGE; }
    template <> std::size_t getComponentId<class GUITextComponent>() { return EComponentId::GUI_TEXT; }

    // Renderer components
    template <> std::size_t getComponentId<class ColorRendererComponent>() { return EComponentId::COLOR_MATERIAL; }
    template <> std::size_t getComponentId<class LitRendererComponent>() { return EComponentId::LIT_MATERIAL; }
    template <> std::size_t getComponentId<class DiffuseRendererComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
    template <> std::size_t getComponentId<class NormalRendererComponent>() { return EComponentId::NORMAL_MATERIAL; }
    template <> std::size_t getComponentId<class SpecularRendererComponent>() { return EComponentId::SPECULAR_MATERIAL; }
    template <> std::size_t getComponentId<class AORendererComponent>() { return EComponentId::AO_MATERIAL; }
};

} // namespace

#include "AComponentsHolder.tpp"

#endif
