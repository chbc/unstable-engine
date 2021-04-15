#include <typeindex>
#include "MeshRenderer.h"

namespace sre
{

template <typename T, typename... TArgs>
T* MeshRenderer::addComponent(TArgs&&... mArgs)
{
    T* newComponent{ nullptr };

    assert(!hasComponent<T>());

    newComponent = new T{ std::forward<TArgs>(mArgs)... };
    int id = getComponentId<T>();
    componentsMap[id] = UPTR<T>{ newComponent };

    return newComponent;
}

template<typename T>
void MeshRenderer::removeComponent()
{
    if (this->hasComponent<T>())
    {
        int id = getComponentId<T>();
        componentsMap.erase(id);
    }
}

template <typename T>
T* MeshRenderer::getComponent()
{
    T* component{ nullptr };

    if (this->hasComponent<T>())
    {
        int id = this->getComponentId<T>();
        component = static_cast<T*>(componentsMap[id].get());
    }

    return component;
}

template<typename T>
bool MeshRenderer::hasComponent()
{
    int id = this->getComponentId<T>();
    return (this->componentsMap.count(id) > 0);
}

template<typename T>
int MeshRenderer::getComponentId()
{
    std::type_index type = typeid(T);
    return type.hash_code();
}

} // namespace
