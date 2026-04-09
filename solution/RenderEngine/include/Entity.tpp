#include "Entity.h"
namespace sre
{

template <typename T>
T* Entity::addComponent()
{
    T* newComponent{ nullptr };

    assert(!this->hasComponent<T>());

    newComponent = new T{ this };
    this->componentsMap[T::ID] = UPTR<T>{ newComponent };

    return newComponent;
}

template<typename T>
void Entity::removeComponent()
{
    if (this->hasComponent<T>())
    {
        componentsMap.erase(T::ID);
    }
}

template <typename T>
T* Entity::getComponent()
{
    T* component{ nullptr };

    if (this->hasComponent<T>())
    {
        component = static_cast<T*>(componentsMap[T::ID].get());
    }
    else
    {
        for (Entity* child : this->childrenList)
        {
            component = child->getComponent<T>();
            if (component)
            {
                break;
            }
		}
    }

    return component;
}

template<typename T>
T* Entity::getBaseComponent()
{
	T* result{ nullptr };

    for (const auto& item : this->componentsMap)
    {
        if (item.second->getBaseId() == T::ID)
        {
            result = static_cast<T*>(item.second.get());
            break;
        }
	}

    return result;
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
    return (this->componentsMap.count(T::ID) > 0);
}

} // namespace
