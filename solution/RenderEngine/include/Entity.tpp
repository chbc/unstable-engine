#include "Entity.h"

namespace sre
{
template <typename T>
T* Entity::addComponent()
{
    if (!this->hasComponent<T>())
    {
        this->componentsMap[T::ID] = VECTOR_UPTR<AEntityComponent>();
	}

    T* newComponent = new T{ this };
    this->componentsMap[T::ID].emplace_back(newComponent);

    return newComponent;
}

template<typename T>
void Entity::removeComponents()
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
        auto& components = this->componentsMap[T::ID];
        component = static_cast<T*>(components[0].get());
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
    for (const auto& item : this->componentsMap)
    {
        auto& components = item.second;
        for (const auto& component : components)
        {
            if (component->getBaseId() == T::ID)
            {
                T* result = static_cast<T*>(component.get());
                return result;
            }
		}
	}

    return nullptr;
}

template <typename T>
void Entity::getComponents(std::vector<T*>& result)
{
    if (this->hasComponent<T>())
    {
        auto& components = this->componentsMap[T::ID];
        for (const auto& component : components)
        {
            result.push_back(static_cast<T*>(component.get()));
		}
    }
    else
    {
        for (Entity* child : this->childrenList)
        {
            child->getComponents<T>(result);
        }
    }
}

template<typename T>
void Entity::getBaseComponents(std::vector<T*>& result)
{
    for (const auto& item : this->componentsMap)
    {
        auto& components = item.second;
        for (const auto& component : components)
        {
            if (component->getBaseId() == T::ID)
            {
                result.push_back(static_cast<T*>(component.get()));
            }
        }
    }
    for (Entity* child : this->childrenList)
    {
        child->getBaseComponents<T>(result);
	}
}

template<typename T>
bool Entity::hasComponent()
{
    return (this->componentsMap.count(T::ID) > 0);
}

template<typename T>
bool Entity::hasBaseComponent()
{
	return (this->componentsMap.count(T::BASE_ID) > 0);
}

} // namespace
