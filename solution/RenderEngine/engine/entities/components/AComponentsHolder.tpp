#include "AEntityComponent.h"

namespace sre
{

template <typename C>
template <typename T>
void AComponentsHolder<C>::addComponent(T *newComponent)
{
	UPTR<T> componentUptr{ newComponent };
	this->components.emplace_back(std::move(componentUptr));

	componentsArray[getComponentID<T>()] = newComponent;
	componentsBitset[getComponentID<T>()] = true;

	newComponent->init();
}

template <typename C>
template <typename T>
T *AComponentsHolder<C>::getComponent()
{
	AEntityComponent *component{ nullptr };
	if (hasComponent<T>())
		component = componentsArray[this->getComponentID<T>()];
	else
		throw "Can't find component!";

	return static_cast<T*>(component);
}

template <typename C>
template<typename T>
bool AComponentsHolder<C>::hasComponent()
{
	static_assert(std::is_base_of<C, T>::value, "Class must be a component!");
	return this->componentsBitset[this->getComponentID<T>()];
}

template <typename C>
template <typename T>
std::size_t AComponentsHolder<C>::getComponentID()
{
	static std::size_t typeID{ generateComponentID() };
	return typeID;
}

template <typename C>
uint16_t AComponentsHolder<C>::generateComponentID()
{
	static uint16_t result{ 0u };
	return result++;
}

} // namespace
