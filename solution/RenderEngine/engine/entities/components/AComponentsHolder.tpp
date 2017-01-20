#include "AEntityComponent.h"

namespace sre
{

template <typename C>
template <typename T>
void AComponentsHolder<C>::addComponent(T *newComponent)
{
	UPTR<T> componentUptr{ newComponent };
	this->components.emplace_back(std::move(componentUptr));

	componentsArray[getComponentId<T>()] = newComponent;
	componentsBitset[getComponentId<T>()] = true;

	newComponent->init();
}

template <typename C>
template <typename T>
T *AComponentsHolder<C>::getComponent()
{
	C *component{ nullptr };

	if (hasComponent<T>())
		component = componentsArray[getComponentId<T>()];
	else
		throw "Can't find component!";

	return static_cast<T*>(component);
}

template <typename C>
template<typename T>
bool AComponentsHolder<C>::hasComponent()
{
	static_assert(std::is_base_of<C, T>::value, "Class must be a component!");
	return this->componentsBitset[getComponentId<T>()];
}

} // namespace
