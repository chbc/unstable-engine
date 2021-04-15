#include "Entity.h"
#include <sstream>

namespace sre
{

Entity::Entity()
{
	this->transform = this->addComponent<TransformComponent>();
	this->parent = nullptr;
	this->alive = false;
	this->enabled = true;
}

Entity::~Entity()
{
	this->children.clear();
}

void Entity::setEnabled(bool value)
{
	this->enabled = value;
}

bool Entity::isEnabled() const
{
	return
	(
		this->enabled && 
		(
			(this->parent == nullptr) ||
			this->parent->isEnabled()
		)
	);
}

void Entity::onStart()
{
    this->alive = true;

    for (auto const &item : this->componentsMap)
        item.second->onStart();

	for (Entity* item : this->children)
		item->onStart();
}

void Entity::update(uint32_t deltaTime)
{
	if (this->enabled)
	{
		for (auto const& item : this->componentsMap)
			item.second->update(deltaTime);

		for (Entity* item : this->children)
			item->update(deltaTime);
	}
}

void Entity::addChild(Entity *child, const std::string& name)
{
	std::string resultName = name;

	if (name.empty())
		resultName = generateEntityId(this->childIndex);

	child->name = resultName;
	this->children.push_back(child);
	child->parent = this;

	this->transform->propagateTransform();
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
	this->enabled = false;
	for (Entity* item : this->children)
		item->destroy();
}

std::string Entity::generateEntityId(uint32_t& index, const std::string& duplicateName)
{
	std::stringstream stream;
	std::string baseName = duplicateName.empty() ? "entity" : duplicateName;
	stream << baseName << "_" << index;
	std::string result = stream.str();
	index++;

	return result;
}

} // namespace
