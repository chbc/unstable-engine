#include "AEntityComponent.h"

namespace sre
{

template <typename C>
template <typename T>
T *AComponentsHolder<C>::getComponent()
{
    C *component{ nullptr };

    if (hasComponent<T>())
        component = componentsMap[getComponentId<T>()].get();
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

template <typename C>
template <typename T>
void AComponentsHolder<C>::addComponent(T *newComponent)
{
    size_t id = getComponentId<T>();
    componentsMap[id] = UPTR<T>{ newComponent };
    componentsBitset[id] = true;
}

template <typename C>
template<typename T>
void AComponentsHolder<C>::removeComponent()
{
    static_assert(std::is_base_of<C, T>::value, "Class must be a component!");

    size_t id = getComponentId<T>();

	if (componentsBitset[id])
	{
		componentsMap.erase(id);
		componentsBitset[id] = false;
	}
}

} // namespace
