#include "Entity.h"
//#include "components/cameras/CameraComponent.h"

namespace sre
{

Entity::Entity()
{
	this->transform = this->addComponent<TransformComponent>();
	this->parent = nullptr;
	this->alive = true;
}

Entity::~Entity()
{
	// TODO: apagar os filhos!
	this->children.clear();
}

void Entity::update(uint32_t deltaTime)
{
	for (auto const &item : this->components)
		item->update(deltaTime);
}

void Entity::addChild(Entity *child)
{
	this->children.push_back(child);
	child->parent = this;
}

TransformComponent *Entity::getTransform()
{
	return this->transform;
}

void Entity::destroy()
{
	this->alive = false;
}

uint16_t Entity::generateComponentID()
{
	static uint16_t result{ 0u };
	return result++;
}


template <typename T>
T *Entity::addComponent()
{
	T *newComponent{ nullptr };

	if (!this->hasComponent<T>())
	{
		newComponent = new T{ this };
		UPTR<T> componentUptr{ newComponent };
		this->components.emplace_back(std::move(componentUptr));

		componentsArray[getComponentID<T>()] = newComponent;
		componentsBitset[getComponentID<T>()] = true;

		newComponent->init();
	}
	else
		throw "Can't add duplicate component!";

	return newComponent;
}

template <typename T>
T *Entity::getComponent()
{
	AEntityComponent *component{ nullptr };
	if (hasComponent<T>())
		component = componentsArray[this->getComponentID<T>()];
	else
		throw "Can't find component!";

	return static_cast<T*>(component);
}

template <typename T>
bool Entity::hasComponent()
{
	static_assert(std::is_base_of<AEntityComponent, T>::value, "T must be an AEntityComponent!");
	return this->componentsBitset[this->getComponentID<T>()];
}

template <typename T>
std::size_t Entity::getComponentID()
{
	static std::size_t typeID{ generateComponentID() };
	return typeID;
}


} // namespace
