#include "AScene.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

namespace sre
{
AScene::AScene(std::string arg_name) : name(arg_name), sceneLoaded(false) { }

Entity* AScene::getEntity(const std::string& name)
{
    Entity* result = nullptr;
    if (this->entities.count(name) > 0)
        result = this->entities[name].get();

    return result;
}

Entity* AScene::createEntity(uint32_t&index, const std::string& name, Entity* parent)
{
    Entity* result = new Entity;

    if (parent != nullptr)
        parent->addChild(result, name);
    else
    {
        std::string resultName = name;
        if (name.empty())
            resultName = Entity::generateEntityId(index);
        else if (this->entities.count(name) > 0)
            resultName = Entity::generateEntityId(index, name);

        result->name = resultName;
        this->entities[resultName] = UPTR<Entity>{ result };
    }

    return result;
}

void AScene::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);
}

void AScene::update(uint32_t elapsedTime)
{
    for (const auto& item : this->entities)
    {
        item.second->onUpdate(elapsedTime);
    }
}

void AScene::onSceneLoaded()
{
    RenderManager* renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();

    for (const auto& item : this->entities)
    {
        renderManager->addEntity(item.second.get());
        item.second->onStart();
    }

    this->sceneLoaded = true;
}

void AScene::destroyAllEntities()
{
    for (auto& item : this->entities)
        item.second->destroy();
}

void AScene::release()
{
    this->entities.clear();
}

} // namespace
