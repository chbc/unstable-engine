#include "Entity.h"
#include <sstream>
#include "MessagesManager.h"
#include "EntityDestroyedMessage.h"
#include "SingletonsManager.h"
#include "BoolEditorProperty.h"

namespace sre
{

Entity::Entity(std::string arg_name) : name(arg_name)
{
	this->transform = this->addComponent<TransformComponent>();
	this->editorProperties.emplace_back(new BoolEditorProperty{ "Enabled", &this->enabled });
}

Entity::~Entity()
{
	this->componentsMap.clear();
	this->childrenList.clear();
	this->children.clear();
}

AEntityComponent* Entity::addComponent(const char* className)
{
	AEntityComponent* newComponent{ nullptr };

	newComponent = AEntityComponent::Create(className, this);
	uint16_t id = newComponent->getId();
	assert(this->componentsMap.count(id) == 0);

	this->componentsMap.emplace(id, newComponent);

	return newComponent;
}

Entity* Entity::createChild(const std::string& childName)
{
	std::string resultName = childName;
	if (childName.empty())
		resultName = generateEntityId(this->childIndex);
	else if (this->children.count(childName) > 0)
		resultName = generateEntityId(this->childIndex, childName);

	Entity* result = new Entity{ resultName };
	this->addChild(result);
	return result;
}

void Entity::addChild(Entity* child)
{
	this->children[child->getName()] = UPTR<Entity>(child);
	child->parent = this;
	this->childrenList.push_back(child);

	this->transform->propagateTransform();
}

Entity* Entity::getChild(uint32_t index)
{
	if (index >= this->children.size())
		throw "[Entity] - getChild - Index out of range!";

	return this->childrenList[index];
}

TransformComponent* Entity::getTransform()
{
	return this->transform;
}

void Entity::destroy()
{
	this->alive = false;
	this->enabled = false;
	for (Entity* item : this->childrenList)
		item->destroy();

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	EntityDestroyedMessage message;
	messagesManager->notify(&message);
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

void Entity::onInit()
{
    this->alive = true;

    for (auto const &item : this->componentsMap)
        item.second->onInit();

	for (Entity* item : this->childrenList)
		item->onInit();
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
