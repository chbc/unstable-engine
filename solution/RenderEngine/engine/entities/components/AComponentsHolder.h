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

private:
	std::bitset<MAX_COMPONENTS> componentsBitset;
	std::array<C*, MAX_COMPONENTS> componentsArray;

public:
	template <typename T> T *getComponent();
	template <typename T> bool hasComponent();

protected:
	template <typename T> void addComponent(T *newComponent);

private:
	template <typename T>
	std::size_t getComponentId();

	// Entity components
	template <> std::size_t getComponentId<class TransformComponent>() { return 1; }
	template <> std::size_t getComponentId<class CameraComponent>() { return 2; }
	template <> std::size_t getComponentId<class DirectionalLightComponent>() { return 3; }
	template <> std::size_t getComponentId<class PointLightComponent>() { return 4; }
	template <> std::size_t getComponentId<class MeshComponent>() { return 5; }

	// Material components
	template <> std::size_t getComponentId<class ColorMaterialComponent>() { return 1; }
	template <> std::size_t getComponentId<class DiffuseMaterialComponent>() { return 2; }
	template <> std::size_t getComponentId<class NormalMaterialComponent>() { return 3; }
	template <> std::size_t getComponentId<class SpecularMaterialComponent>() { return 4; }
};

} // namespace

#include "AComponentsHolder.tpp"

#endif
