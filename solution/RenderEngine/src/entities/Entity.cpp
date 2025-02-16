#include "Entity.h"
#include <sstream>
#include "MessagesManager.h"
#include "EntityDestroyedMessage.h"
#include "SingletonsManager.h"
#include "BoolEditorProperty.h"

namespace sre
{

const char* Entity::BASE_CLASS_NAME = Entity::AddType<Entity>("Entity");

Entity::Entity(std::string arg_name) : name(arg_name)
{
	this->transform = this->addComponent<TransformComponent>();
	this->addEditorProperty(new BoolEditorProperty{ "Enabled", &this->enabled });
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

const char* Entity::getClassName() const
{
	return BASE_CLASS_NAME;
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
	editorProperty->onValueDeserializedCallback = std::bind(&Entity::onValueDeserialized, this);
	editorProperty->onValueChangedCallback = std::bind(&Entity::onValueChanged, this);
	this->editorProperties.emplace_back(editorProperty);
}

Entity* Entity::clone()
{
	Entity* result = Create(this->name, this->getClassName());
	for (int i = 0; i < this->editorProperties.size(); ++i)
	{
		SPTR<AEditorProperty>& destination = result->editorProperties[i];
		this->editorProperties[i]->copy(destination.get());
	}

	for (const auto& item : this->componentsMap)
	{
		AEntityComponent* resultComponent = nullptr;
		std::string className = item.second->getClassName();
		if (className == "TransformComponent")
		{
			resultComponent = result->getComponent<TransformComponent>();
		}
		else
		{
			resultComponent = result->addComponent(item.second->getClassName());
		}

		item.second->clone(resultComponent);
	}

	return result;
}

AEditorProperty* Entity::findProperty(const std::string& title)
{
	AEditorProperty* result{ nullptr };
	for (const auto& item : this->editorProperties)
	{
		if (item->title == title)
		{
			result = item.get();
			break;
		}
	}

	return result;
}

Entity* Entity::Create(std::string arg_name, const std::string& className)
{
	Entity* result{ nullptr };

	if (!className.empty())
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

} // namespace
