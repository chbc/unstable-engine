#include "Entity.h"

namespace sre
{

Entity::Entity() : AComponentsHolder<AEntityComponent>()
{
	this->transform = this->addComponent<TransformComponent>();
	this->parent = nullptr;
	this->alive = false;
}

Entity::~Entity()
{
	this->children.clear();
}

void Entity::onStart()
{
    this->alive = true;

    for (auto const &item : this->components)
        item->onStart();
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

Entity *Entity::getChild(uint32_t index)
{
	if (index >= this->children.size())
		throw "[Entity] - getChild - Index out of range!";

	return this->children[index];
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
