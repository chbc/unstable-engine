#include "MeshComponent.h"
#include "MeshData.h"
#include "MaterialEditorProperty.h"
#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "FileUtils.h"

namespace sre
{

IMPLEMENT_COMPONENT(MeshComponent)

MeshComponent::MeshComponent(Entity *entity)
    : AEntityComponent(entity), opaque(true), material(nullptr), mesh(nullptr)
{
    this->addEditorProperty(new MeshEditorProperty{ "Mesh", &this->mesh });
    this->addEditorProperty(new MaterialEditorProperty{ "Material", &this->material});
}

MeshComponent::~MeshComponent()
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    assetsManager->releaseMesh(this->mesh);
    assetsManager->releaseMaterial(this->material);
}

Material *MeshComponent::getMaterial()
{
    return this->material;
}

void MeshComponent::setIsOpaque(bool value)
{
    this->opaque = value;
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

	std::string materialPath = FileUtils::getAbsoluteContentPath("engine/media/DefaultMaterial.mat");
    this->material = assetsManager->loadMaterial(materialPath.c_str());
}

} // namespace
