#include "Entity.h"
#include <engine/scene/SceneManager.h>
#include <engine/math/Transform.h>

namespace sre
{

Entity::Entity()
{
	this->parent = NULL;
	this->id = SceneManager::getInstance()->generateNodeId();
	this->transform = new Transform;
}

/*
Node::~Node()
{
	delete this->transform;
	// TODO: apagar os filhos!
}
*/

void Entity::addChild(Entity *child)
{
	// TODO: implementar
}

Transform *Entity::getTransform()
{
	return this->transform;
}

void Entity::setPosition(Vector position)
{
	this->transform->setPosition(position);
}

void Entity::setScale(Vector scale)
{
	this->transform->setScale(scale);
}

void Entity::setRotation(Vector axis, float angle)
{
	this->transform->setRotation(axis, angle);
}

} // namespace
