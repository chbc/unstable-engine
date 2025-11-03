#include "Entity.h"
#include <sstream>
#include "MessagesManager.h"
#include "EntityDestroyedMessage.h"
#include "MeshComponent.h"
#include "EditorMessages.h"
#include "SingletonsManager.h"
#include "BoolEditorProperty.h"

namespace sre
{

const char* Entity::BASE_CLASS_NAME = Entity::AddType<Entity>("Entity");

Entity::Entity(std::string arg_name) : name(arg_name)
{
	this->transform = this->addComponent<TransformComponent>();
	this->addEditorProperty(new BoolEditorProperty{ arg_name.c_str(), &this->enabled});
}

Entity::~Entity()
{
	this->componentsMap.clear();
	this->childrenList.clear();
	this->children.clear();
	this->parent = nullptr;
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

Entity* Entity::addChild(Entity* child)
{
	return this->addChild(UPTR<Entity>{ child });
}

Entity* Entity::addChild(UPTR<Entity>& child)
{
	child->parent = this;
	const char* childName = child->getName();
	this->children[childName] = std::move(child);
	
	Entity* result = this->children[childName].get();
	this->childrenList.push_back(result);

	const glm::mat4& transformMatrix = this->transform->getMatrix();
	result->getTransform()->updateLocalValues(transformMatrix);
	this->transform->propagateTransform();

	return result;
}

void Entity::removeChild(Entity* child)
{
	if (this->children.count(child->getName()) > 0)
	{
		this->children.erase(child->getName());
	
		auto it = std::find(this->childrenList.begin(), this->childrenList.end(), child);
		if (it != this->childrenList.end())
		{
			this->childrenList.erase(it);
		}
	
		child->parent = nullptr;
	}
}

Entity* Entity::getChild(size_t index)
{
	if (index >= this->children.size())
		throw "[Entity] - getChild - Index out of range!";

	return this->childrenList[index];
}

Entity* Entity::getChild(const std::string& name)
{
	Entity* result{ nullptr };
	if (this->children.count(name) > 0)
	{
		result = this->children[name].get();
	}
	else
	{
		for (Entity* item : this->childrenList)
		{
			result = item->getChild(name);
			if (result)
			{
				break;
			}
		}
	}

	return result;
}

UPTR<Entity> Entity::moveChild(const std::string& name)
{
	UPTR<Entity> result{ nullptr };

	if (this->children.count(name) > 0)
	{
		result = std::move(this->children[name]);
		this->children.erase(name);
		auto it = std::find(this->childrenList.begin(), this->childrenList.end(), result.get());
		if (it != this->childrenList.end())
		{
			this->childrenList.erase(it);
		}
		result->parent = nullptr;
	}

	return result;
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
	EntityDestroyedMessage message{ this };
	messagesManager->notify(&message);
}

void Entity::setEnabled(bool value, bool changeChildren)
{
	this->enabled = value;

	if (changeChildren)
	{
		for (Entity* item : this->childrenList)
		{
			item->setEnabled(value, changeChildren);
		}
	}
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

void Entity::getBounds(Bounds& bounds) const
{
	bool baseEntity = true;
	this->getBounds(bounds, baseEntity);
}

void Entity::setDontShowInEditorSceneTree(bool value)
{
	this->dontShowInEditorSceneTree = value;
}

bool Entity::raycast(const Ray& ray, float& distance)
{
	bool result = false;

	if (this->hasComponent<MeshComponent>())
	{
		ARenderableComponent* renderableComponent = this->getComponent<MeshComponent>();
		TransformComponent* transform = this->getTransform();
		Bounds bounds = renderableComponent->getBounds();

		const glm::mat4& modelMatrix = transform->getMatrix();
		if (bounds.intersects(ray, modelMatrix, distance))
		{
			result = true;
		}
	}
	else
	{
		for (Entity* item : this->childrenList)
		{
			if (item->raycast(ray, distance))
			{
				result = true;
				break;
			}
		}
	}

	return result;
}

Entity* Entity::raycastChildren(const Ray& ray, float maxDistance)
{
	Entity* result{ nullptr };

	float minDistance = maxDistance;
	for (Entity* item : this->childrenList)
	{
		float distance = 0;
		if (item->raycast(ray, distance) && (distance < minDistance))
		{
			result = item;
			minDistance = distance;
		}
	}

	return result;
}

bool Entity::isStored() const
{
	return (this->propertiesStored && this->componentsStored && this->childrenStored);
}

bool Entity::isSaved() const
{
	return (this->propertiesSaved && this->componentsSaved && this->childrenSaved);
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
	editorProperty->onValueSerializedCallback = std::bind(&Entity::onPropertySerialized, this);
	editorProperty->onValueDeserializedCallback = std::bind(&Entity::onPropertyDeserialized, this);
	editorProperty->onValueChangedCallback = std::bind(&Entity::onPropertyChanged, this);
	this->editorProperties.emplace_back(editorProperty);
}

void Entity::onPropertyDeserialized()
{
	this->propertiesStored = false;
}

void Entity::onPropertyChanged()
{
	this->propertiesSaved = false;
	this->propertiesStored = false;

	if (this->parent != nullptr)
	{
		this->parent->onChildChanged();
	}

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify<EntityChangedEditorMessage>();
}

void Entity::onComponentDeserialized()
{
	this->componentsStored = false;
}

void Entity::onComponentChanged()
{
	this->componentsSaved = false;
	this->componentsStored = false;

	if (this->parent != nullptr)
	{
		this->parent->onChildChanged();
	}

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify<EntityChangedEditorMessage>();
}

void Entity::onChildChanged()
{
	this->childrenSaved = false;
	this->childrenStored = false;

	if (this->parent != nullptr)
	{
		this->parent->onChildChanged();
	}
}

void Entity::getBounds(Bounds& bounds, bool& baseEntity) const
{
	for (const auto& item : this->componentsMap)
	{
		if (item.second->isEnabled() && item.second->isRenderable())
		{
			ARenderableComponent* renderableComponent = static_cast<ARenderableComponent*>(item.second.get());
			const Bounds& componentBounds = renderableComponent->getBounds();

			if (baseEntity)
			{
				bounds = componentBounds;
				baseEntity = false;
			}
			else
			{
				bounds.add(componentBounds);
			}
		}
	}

	for (Entity* item : this->childrenList)
	{
		if (item->isEnabled())
		{
			item->getBounds(bounds, baseEntity);
		}
	}
}

void Entity::setPropertiesSaved()
{
	this->propertiesSaved = true;
}

void Entity::setComponentsSaved()
{
	this->componentsSaved = true;
}

void Entity::setChildrenSaved()
{
	this->childrenSaved = true;
}

void Entity::setStored(bool value)
{
	this->propertiesStored = value;
	this->componentsStored = value;
	this->childrenStored = value;

	for (auto& item : this->editorProperties)
	{
		item->setStored(value);
	}

	for (auto& item : this->componentsMap)
	{
		item.second->setStored(value);
	}

	for (auto& item : this->childrenList)
	{
		item->setStored(value);
	}
}

bool Entity::isPropertiesSaved() const
{
	return this->propertiesSaved;
}

bool Entity::isComponentsSaved() const
{
	return this->componentsSaved;
}

bool Entity::isChildrenSaved() const
{
	return this->childrenSaved;
}

bool Entity::isPropertiesStored() const
{
	return this->propertiesStored;
}

bool Entity::isComponentsStored() const
{
	return this->componentsStored;
}

bool Entity::isChildrenStored() const
{
	return this->childrenStored;
}

bool Entity::isAsset() const
{
	return !this->filePath.empty();
}

Entity* Entity::clone()
{
	Entity* result = Create(this->name, this->getClassName());
	result->name = this->name;
	result->filePath = this->filePath;

	// properties
	for (int i = 0; i < this->editorProperties.size(); ++i)
	{
		SPTR<AEditorProperty>& destination = result->editorProperties[i];
		this->editorProperties[i]->copy(destination.get());
	}

	// components
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
		resultComponent->onClone();
	}

	// children
	for (Entity* item : this->childrenList)
	{
		Entity* childEntity = item->clone();
		result->addChild(childEntity);
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
