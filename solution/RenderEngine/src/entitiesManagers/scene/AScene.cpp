#include "AScene.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "AssetsManager.h"
#include "FileUtils.h"

namespace sre
{
uint32_t AScene::EntityIndex = 0;

AScene::AScene(std::string arg_name) : name(arg_name), sceneLoaded(false) { }

AScene::~AScene()
{
    this->entities.clear();
}

Entity* AScene::getEntity(const std::string& name)
{
    Entity* result = nullptr;
    if (this->entities.count(name) > 0)
    {
        result = this->entities[name].get();
    }

    return result;
}

Entity* AScene::createEntity(std::string name, Entity* parent, const std::string& className, const std::string& fileName)
{
    Entity* result = nullptr;
    this->resolveName(name);

    if (!fileName.empty())
    {
        AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
        result = assetsManager->loadEntity(fileName.c_str(), name);
    }
    else
    {
        result = Entity::Create(name, className);
    }

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

Entity* AScene::spawnEntity(const char* fileName, const glm::vec3& position)
{
    Entity* entity = this->createEntity("", nullptr, "", fileName);

    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    renderManager->addEntity(entity);

    entity->getTransform()->setPosition(position);

    return entity;
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
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();

    for (const auto& item : this->entities)
    {
        renderManager->addEntity(item.second.get());
    }

    this->sceneLoaded = true;
}

void AScene::resolveName(std::string& name)
{
    if (name.empty())
    {
        name = this->generateEntityId();
    }
    else if (this->entities.count(name) > 0)
    {
        name = this->generateEntityId(name);
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
