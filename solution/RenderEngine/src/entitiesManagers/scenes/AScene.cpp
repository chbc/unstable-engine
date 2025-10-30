#include "AScene.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "AssetsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "FileUtils.h"

namespace sre
{
uint32_t AScene::EntityIndex = 0;

AScene::AScene(std::string arg_name, std::string arg_filePath) 
    : name(arg_name), label(arg_name), filePath(arg_filePath)
{
    Action* action = new Action{ [&](void* message) {this->onEntityChanged(message); } };
    this->entityChangedAction = SPTR<Action>(action);

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->addListener<EntityChangedEditorMessage>(this->entityChangedAction.get());
}

AScene::~AScene()
{
    this->entities.clear();

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->removeListener<EntityChangedEditorMessage>(this->entityChangedAction.get());
}

Entity* AScene::getEntity(const std::string& entityName)
{
    Entity* result = nullptr;
    if (this->entities.count(entityName) > 0)
    {
        result = this->entities[entityName].get();
    }

    return result;
}

Entity* AScene::createEntity(std::string name, Entity* parent, const std::string& className)
{
    Entity* result = nullptr;
    this->resolveName(name);

    result = Entity::Create(name, className);

    if (parent != nullptr)
    {
        parent->addChild(result);
    }
    else
    {
        this->entities[name] = UPTR<Entity>{ result };
    }

    return result;
}

Entity* AScene::createEntityFromFile(std::string filePath, Entity* parent)
{
    Entity* result = nullptr;
	std::string name = FileUtils::getFileName(filePath);
    this->resolveName(name);

    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    result = assetsManager->loadEntity(this, filePath.c_str(), name);

    if (parent != nullptr)
    {
        result = parent->addChild(result);
    }
    else
    {
        this->entities[name] = UPTR<Entity>{ result };
    }

    return result;
}

Entity* AScene::duplicateEntity(Entity* entity)
{
    Entity* result = nullptr;
    if (entity != nullptr)
    {
        std::string name = entity->name;
        this->resolveName(name);
        result = entity->clone();
        result->name = name;
        this->entities[name] = UPTR<Entity>{ result };

		TransformComponent* resultTransform = result->getTransform();
		TransformComponent* entityTransform = entity->getTransform();
        resultTransform->setPosition(entityTransform->getPosition());
		resultTransform->setRotation(entityTransform->getRotation());
		resultTransform->setScale(entityTransform->getScale());
    }
	return result;
}

void AScene::moveEntityToBeChild(const std::string& entityName, Entity* targetParent)
{
    if (this->entities.count(entityName) > 0)
    {
        UPTR<Entity>& result = this->entities[entityName];
	    targetParent->addChild(std::move(result));

        this->entities.erase(entityName);
	}
}

void AScene::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);
}

void AScene::onSceneLoaded()
{
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    for (const auto& item : this->entities)
    {
        renderManager->addEntity(item.second.get());
    }
}

void AScene::initEntities()
{
    for (const auto& item : this->entities)
    {
        item.second->onInit();
    }
}

void AScene::update(float elapsedTime)
{
    for (const auto& item : this->entities)
    {
        item.second->onUpdate(elapsedTime);
    }
}

void AScene::resolveName(std::string& entityName)
{
    if (entityName.empty())
    {
        entityName = this->generateEntityId();
    }
    else if (this->entities.count(entityName) > 0)
    {
        entityName = this->generateEntityId(entityName);
    }
}

std::string AScene::generateEntityId(const std::string& duplicateName)
{
    std::stringstream stream;
    std::string baseName = duplicateName.empty() ? "entity" : duplicateName;
    stream << baseName << "_" << EntityIndex;
    std::string result = stream.str();
    EntityIndex++;

    return result;
}

void AScene::onEntityChanged(void* data)
{
    this->label = this->name + "*";
}

void AScene::onSceneSaved()
{
    this->label = this->name;
}

} // namespace
