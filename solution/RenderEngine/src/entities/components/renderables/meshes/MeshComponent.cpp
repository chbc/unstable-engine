#include "MeshComponent.h"
#include "MeshData.h"
#include "MaterialEditorProperty.h"
#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "RenderManager.h"

namespace sre
{

IMPLEMENT_COMPONENT(MeshComponent)

MeshComponent::MeshComponent(Entity *entity)
    : AEntityComponent(entity), opaque(true), material(nullptr), mesh(nullptr)
{
    this->addEditorProperty(new MeshEditorProperty{ "Mesh", &this->mesh });
    this->addEditorProperty(new MaterialEditorProperty{ "Material", &this->material});
}

Material *MeshComponent::getMaterial()
{
    return this->material;
}

void MeshComponent::setIsOpaque(bool value)
{
    this->opaque = value;
}

bool MeshComponent::isAbleToBeRendered()
{
    return
    (
        (this->mesh->meshData.get() != nullptr) &&
        !this->mesh->meshData->indices.empty()
    );
}

bool MeshComponent::isOpaque()
{
    return this->opaque;
}

void MeshComponent::load(const char* file)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();
    this->mesh = assetsManager->loadMesh(file);

    RenderManager* renderManager = singletonsManager->get<RenderManager>();
    renderManager->addEntity(this->getEntity());
    // XXX renderManager->onSceneLoaded();
}

} // namespace
