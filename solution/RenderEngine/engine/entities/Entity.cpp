#include "Entity.h"
//#include "components/cameras/CameraComponent.h"

namespace sre
{

Entity::Entity() : AComponentsHolder<AEntityComponent>()
{
	this->transform = this->addComponent<TransformComponent>();
	this->parent = nullptr;
	this->alive = true;
}

Entity::~Entity()
{
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

} // namespace
