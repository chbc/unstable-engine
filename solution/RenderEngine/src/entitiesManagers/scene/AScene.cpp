#include "AScene.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "AssetsManager.h"

namespace sre
{
uint32_t AScene::EntityIndex = 0;

AScene::AScene(std::string arg_name, std::string arg_filePath) : name(arg_name), filePath(arg_filePath)
{
    this->renderManager = SingletonsManager::getInstance()->get<RenderManager>();
}

AScene::~AScene()
{
    this->entities.clear();
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

Entity* AScene::createEntity(std::string entityName, Entity* parent, const std::string& className, const std::string& filePath)
{
    Entity* result = nullptr;
    this->resolveName(entityName);

    if (!filePath.empty())
    {
        AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
        result = assetsManager->loadEntity(filePath.c_str(), entityName);
    }
    else
    {
        result = Entity::Create(entityName, className);
    }

    if (parent != nullptr)
    {
        parent->addChild(result);
    }
    else
    {
        this->entities[entityName] = UPTR<Entity>{ result };
    }

    return result;
}

void AScene::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);
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

void AScene::onSceneLoaded()
{
    for (const auto& item : this->entities)
    {
        renderManager->addEntity(item.second.get());
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

} // namespace
