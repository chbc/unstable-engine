#include "MeshComponent.h"
#include "MeshData.h"
#include "MaterialEditorProperty.h"
#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "RenderManager.h"
#include "FileUtils.h"
#include "ABaseMaterial.h"

namespace sre
{

IMPLEMENT_COMPONENT(MeshComponent)

MeshComponent::MeshComponent(Entity *entity) : ARenderableComponent(entity)
{
    this->addEditorProperty(new MeshEditorProperty{ "Mesh", &this->mesh, &this->modelPath });
    this->addEditorProperty(new MaterialEditorProperty{ "Material", &this->material});
}

MeshComponent::~MeshComponent()
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    assetsManager->releaseModel(this->modelPath.c_str());
    assetsManager->releaseMaterial(this->material);
}

ABaseMaterial *MeshComponent::getMaterial()
{
    return this->material;
}

void MeshComponent::setIsOpaque(bool value)
{
    this->opaque = value;
}

void MeshComponent::setWireframeMode(bool value)
{
    this->wireframe = value;
}

EDrawMode::Type MeshComponent::getDrawMode()
{
    return this->wireframe ? EDrawMode::LINES : EDrawMode::TRIANGLES;
}

void MeshComponent::loadMaterial(const char* filePath)
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    assetsManager->releaseMaterial(this->material);

    this->material = assetsManager->loadMaterial(filePath);
    this->refreshMesh();
}

bool MeshComponent::isMaterialStandard()
{
    return this->material->isStandard();
}

void MeshComponent::setLineWidth(float value)
{
	this->lineWidth = value;
}

bool MeshComponent::isOpaque()
{
    return this->opaque;
}

void MeshComponent::load(Model* model, const char* meshName)
{
    this->mesh = model->getMesh(meshName);
	this->modelPath = model->getFilePath();
    this->bounds.setup(this->mesh->vertexData);

    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();

    this->material = assetsManager->loadMaterial("engine\\media\\DefaultMaterial.mat");
}

void MeshComponent::onPropertyDeserialized()
{
	ARenderableComponent::onPropertyDeserialized();

    if ((this->mesh != nullptr) && (!this->mesh->vertexData.empty()))
    {
        this->bounds.setup(this->mesh->vertexData);
    }
}

void MeshComponent::onPropertyChanged()
{
	ARenderableComponent::onPropertyChanged();
    this->bounds.setup(this->mesh->vertexData);
    this->refreshMesh();
}

void MeshComponent::setMaterial(ABaseMaterial* arg_material)
{
    if (this->material != nullptr)
    {
        AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
        assetsManager->releaseMaterial(this->material);
    }

    this->material = arg_material;
}

void MeshComponent::refreshMesh()
{
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    renderManager->removeMesh(this);
    renderManager->addMesh(this);
}

} // namespace
