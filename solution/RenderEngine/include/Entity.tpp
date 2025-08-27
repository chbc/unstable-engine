namespace sre
{

template <typename T>
T* Entity::addComponent()
{
    T* newComponent{ nullptr };

    T::SetupChildId();
    assert(!this->hasComponent<T>());

    newComponent = new T{ this };
    uint16_t id = this->getComponentId<T>();
    this->componentsMap[id] = UPTR<T>{ newComponent };

    return newComponent;
}

template<typename T>
void Entity::removeComponent()
{
    if (this->hasComponent<T>())
    {
        uint16_t id = getComponentId<T>();
        componentsMap.erase(id);
    }
}

template <typename T>
T* Entity::getComponent()
{
    T* component{ nullptr };

    if (this->hasComponent<T>())
    {
        uint16_t id = this->getComponentId<T>();
        component = static_cast<T*>(componentsMap[id].get());
    }

    return component;
}

template <typename T>
void Entity::getComponents(std::vector<T*>& result)
{
    T* component = this->getComponent<T>();
    if (component)
    {
		result.push_back(component);
    }

    for (Entity* child : this->childrenList)
    {
		child->getComponents<T>(result);
	}
}

template<typename T>
bool Entity::hasComponent()
{
    uint16_t id = this->getComponentId<T>();
    return (this->componentsMap.count(id) > 0);
}

template<typename T>
uint16_t Entity::getComponentId()
{
    return T::ID;
}

} // namespace
