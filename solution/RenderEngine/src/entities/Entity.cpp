#include "Entity.h"
#include <sstream>
#include "MessagesManager.h"
#include "EntityDestroyedMessage.h"
#include "SingletonsManager.h"
#include "BoolEditorProperty.h"

namespace sre
{

IMPLEMENT_ENTITY(Entity)

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

Entity* Entity::createChild(const std::string& childName, const char* className)
{
	std::string resultName = childName;
	if (childName.empty())
		resultName = generateEntityId(this->childIndex);
	else if (this->children.count(childName) > 0)
		resultName = generateEntityId(this->childIndex, childName);

	Entity* result = Create(resultName, className);
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

Entity* Entity::getChild(size_t index)
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

void Entity::onUpdate(float elapsedTime)
{
	if (this->enabled)
	{
		for (auto const& item : this->componentsMap)
		{
			if (item.second->isEnabled())
				item.second->onUpdate(elapsedTime);
		}

		for (Entity* item : this->childrenList)
			item->onUpdate(elapsedTime);
	}
}

void Entity::addEditorProperty(AEditorProperty* editorProperty)
{
	editorProperty->onValueChanged = std::bind(&Entity::onValueChanged, this);
	this->editorProperties.emplace_back(editorProperty);
}

Entity* Entity::Create(std::string arg_name, const char* className)
{
	Entity* result{ nullptr };

	if (className != nullptr)
	{
		EntityTypes* types = EntityTypes::getInstance();
		size_t key = std::hash<std::string>{}(className);

		assert(types->typesMap.count(key) > 0);

		result = types->typesMap[key](arg_name);
	}
	else
	{
		result = new Entity{ arg_name };
	}

	return result;
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
