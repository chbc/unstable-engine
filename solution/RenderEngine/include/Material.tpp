#include <cassert>

namespace sre
{

template <typename T, typename... TArgs>
T* Material::addComponent(TArgs&&... mArgs)
{
    T* newComponent{ nullptr };

    assert(!this->hasComponent<T>());

    newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
    size_t id = this->getComponentId<T>();
    this->componentsMap[id] = UPTR<T>{ newComponent };
    this->componentsBitset[id] = true;

    return newComponent;
}

template<typename T>
void Material::removeComponent()
{
    if (this->hasComponent<T>())
    {
        int id = this->getComponentId<T>();
        this->componentsMap.erase(id);
        this->componentsBitset[id] = false;
    }
}

template <typename T>
T* Material::getComponent()
{
    T* component{ nullptr };

    if (this->hasComponent<T>())
    {
        int id = this->getComponentId<T>();
        component = static_cast<T*>(this->componentsMap[id].get());
    }

    return component;
}

template<typename T>
bool Material::hasComponent()
{
    bool result = false;
    size_t id = this->getComponentId<T>();

    if (id < EComponentId::SIZE)
        result = this->componentsBitset[id];

    return result;
}

} // namespace
