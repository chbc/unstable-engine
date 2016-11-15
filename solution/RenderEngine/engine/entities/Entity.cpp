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

} // namespace
