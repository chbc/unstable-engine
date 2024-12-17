#include <cassert>

namespace sre
{

template <typename T, typename... TArgs>
T* Material::addComponent(TArgs&&... mArgs)
{
    T* newComponent{ nullptr };

    assert(!this->hasComponent<T>());

    newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
    size_t id = T::ID;
    this->componentsMap[id] = UPTR<T>{ newComponent };
    this->componentsBitset[id] = true;

    return newComponent;
}

template<typename T>
void Material::removeComponent()
{
    if (this->hasComponent<T>())
    {
        int id = T::ID;
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
        int id = T::ID;
        component = static_cast<T*>(this->componentsMap[id].get());
    }

    return component;
}

template<typename T>
bool Material::hasComponent()
{
    uint16_t id = T::ID;
    return (this->componentsMap.count(id) > 0);
}

} // namespace
