#include "Node.h"
#include <engine/scene/SceneManager.h>

namespace sre
{

Node::Node()
{
	this->parent = NULL;
	this->id = SceneManager::getInstance()->generateNodeId();
	this->transform = new Transform;
}

Node::~Node()
{
	delete this->transform;
	// TODO: apagar os filhos!
}

void Node::addChild(Node *child)
{
	// TODO: implementar
}

Transform *Node::getTransform()
{
	return this->transform;
}

void Node::setPosition(Vector position)
{
	this->transform->setPosition(position);
}

void Node::setScale(Vector scale)
{
	this->transform->setScale(scale);
}

void Node::setRotation(Vector axis, float angle)
{
	this->transform->setRotation(axis, angle);
}

} // namespace
