#ifndef _A_COMPONENTS_HOLDER_H_
#define _A_COMPONENTS_HOLDER_H_

#include <engine/utils/memory_aliases.h>
#include <bitset>
#include <array>

namespace sre
{

constexpr size_t MAX_COMPONENTS{ 10 };

template <typename C>
class AComponentsHolder
{
protected:
	VECTOR_UPTR<C> components;
	std::bitset<MAX_COMPONENTS> componentsBitset;

private:
	std::array<C*, MAX_COMPONENTS> componentsArray;

public:
	template <typename T> T *getComponent();
	std::vector<C*> getComponents();
	template <typename T> bool hasComponent();

protected:
	template <typename T> void addComponent(T *newComponent);

private:
	template <typename T>
	std::size_t getComponentId();

	// Entity components
	template <> std::size_t getComponentId<class TransformComponent>() { return 0; }
	template <> std::size_t getComponentId<class CameraComponent>() { return 1; }
	template <> std::size_t getComponentId<class DirectionalLightComponent>() { return 2; }
	template <> std::size_t getComponentId<class PointLightComponent>() { return 3; }
	template <> std::size_t getComponentId<class MeshComponent>() { return 4; }

	// Material components
	template <> std::size_t getComponentId<class ColorMaterialComponent>() { return 0; }
	template <> std::size_t getComponentId<class DiffuseMaterialComponent>() { return 1; }
	template <> std::size_t getComponentId<class NormalMaterialComponent>() { return 2; }
	template <> std::size_t getComponentId<class SpecularMaterialComponent>() { return 3; }
	template <> std::size_t getComponentId<class AmbientOcclusionMaterialComponent>() { return 4; }

	// Renderer components
	template <> std::size_t getComponentId<class ColorRendererComponent>() { return 0; }
	template <> std::size_t getComponentId<class DiffuseRendererComponent>() { return 1; }
	template <> std::size_t getComponentId<class NormalRendererComponent>() { return 2; }
	template <> std::size_t getComponentId<class SpecularRendererComponent>() { return 3; }
	template <> std::size_t getComponentId<class AORendererComponent>() { return 4; }
};

} // namespace

#include "AComponentsHolder.tpp"

#endif
