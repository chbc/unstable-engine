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
	this->componentsMap.clear();
	this->childrenList.clear();
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

	for (Entity* item : this->childrenList)
		item->onStart();
}

void Entity::onUpdate(float deltaTime)
{
	if (this->enabled)
	{
		for (auto const& item : this->componentsMap)
		{
			if (item.second->isEnabled())
				item.second->onUpdate(deltaTime);
		}

		for (Entity* item : this->childrenList)
			item->onUpdate(deltaTime);
	}
}

void Entity::addChild(Entity *child, const std::string& childName)
{
	std::string resultName = childName;

	if (childName.empty())
		resultName = generateEntityId(this->childIndex);
	else if (this->children.count(childName) > 0)
		resultName = generateEntityId(this->childIndex, childName);

	child->name = resultName;
	this->children[resultName] = UPTR<Entity>(child);
	child->parent = this;
	this->childrenList.push_back(child);

	this->transform->propagateTransform();
}

Entity *Entity::getChild(uint32_t index)
{
	if (index >= this->children.size())
		throw "[Entity] - getChild - Index out of range!";

	return this->childrenList[index];
}

TransformComponent *Entity::getTransform()
{
	return this->transform;
}

void Entity::destroy()
{
	this->alive = false;
	this->enabled = false;
	for (Entity* item : this->childrenList)
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
