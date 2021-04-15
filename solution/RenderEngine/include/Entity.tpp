namespace sre
{

template <typename T, typename... TArgs>
T* Entity::addComponent(TArgs&&... mArgs)
{
    T* newComponent{ nullptr };

    assert(!this->hasComponent<T>());

    newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
    int id = this->getComponentId<T>();
    this->componentsMap[id] = UPTR<T>{ newComponent };

    return newComponent;
}

template<typename T>
void Entity::removeComponent()
{
    if (this->hasComponent<T>())
    {
        int id = getComponentId<T>();
        componentsMap.erase(id);
    }
}

template <typename T>
T* Entity::getComponent()
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
bool Entity::hasComponent()
{
    int id = this->getComponentId<T>();
    return (this->componentsMap.count(id) > 0);
}

template<typename T>
int Entity::getComponentId()
{
    return T::ID;
}

} // namespace
