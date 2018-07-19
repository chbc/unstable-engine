#include "Renderer.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/core/graphics/MatrixManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>

#include "shadersSetup/LightRendererShaderSetup.h"

namespace sre
{

Renderer::Renderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
    
    // ### COLOCAR NUM FACTORY
    for (int i = EComponentId::COLOR_MATERIAL; i <= EComponentId::AO_MATERIAL; i++)
    {
        if (material->componentsBitset[i])
        {
            switch (i)
            {
                case EComponentId::COLOR_MATERIAL:
                    this->addComponent<ColorRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::DIFFUSE_MATERIAL:
                    this->addComponent<DiffuseRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::NORMAL_MATERIAL:
                    this->addComponent<NormalRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::SPECULAR_MATERIAL:
                    this->addComponent<SpecularRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::AO_MATERIAL:
                    this->addComponent<AORendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                default: break;
            }
        }
    }

    BaseRendererShaderSetup *item = new BaseRendererShaderSetup(this->shaderManager, this->graphicsWrapper);
    this->shaderSetupItems[typeid(BaseRendererShaderSetup).name()] = UPTR<BaseRendererShaderSetup>(item);

    if (material->receivesLight)
    {
        this->lightData.receivesLight = true;
        item = new LightRendererShaderSetup(this->shaderManager, this->graphicsWrapper);
        this->shaderSetupItems[typeid(LightRendererShaderSetup).name()] = UPTR<BaseRendererShaderSetup>(item);
    }

    if (material->receivesShadow)
    {
        this->lightData.receivesShadow = true;
        item = new ShadowRendererShaderSetup(this->shaderManager, this->graphicsWrapper);
        this->shaderSetupItems[typeid(ShadowRendererShaderSetup).name()] = UPTR<BaseRendererShaderSetup>(item);
    }
}

Renderer::~Renderer()
{
    for (MeshComponent *item : this->meshes)
        this->graphicsWrapper->deleteBuffers(item);
}

void Renderer::onSceneLoaded()
{
    this->loadShader();

    for (const auto &item : this->shaderSetupItems)
        item.second->onSceneLoaded(this->shader);

    for (const UPTR<ColorRendererComponent> &item : this->components)
        item->onSceneLoaded(this->shader);
}

void Renderer::loadShader()
{
    for (const auto &item : this->shaderSetupItems)
        item.second->getLightData(this->lightData);

    this->shader = this->shaderManager->loadShader(this->componentsBitset, this->lightData);
}

void Renderer::addMesh(MeshComponent *mesh)
{
    this->meshes.push_back(mesh);
    this->graphicsWrapper->createVAO(mesh);
    this->graphicsWrapper->createEBO(mesh);
}

void Renderer::render(MatrixManager *matrixManager, const glm::vec3 &cameraPosition)
{
    // Shader setup
    this->shaderManager->enableShader(this->shader);

    for (const auto &item : this->shaderSetupItems)
        item.second->setupShaderValues(this->shader);

    this->shaderManager->setVec3(shader, ShaderVariables::CAMERA_POSITION, &cameraPosition[0]);

    for (MeshComponent *mesh : this->meshes)
    {
        // Matrix setup
        TransformComponent *transform = mesh->getTransform();
        glm::mat4 modelMatrix = transform->getMatrix();
        this->shaderManager->setMat4(this->shader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

        this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
        for (const UPTR<ColorRendererComponent> &item : this->components)
        {
            item->setupShaderValues(mesh, this->shader);
            item->preDraw();
        }

        this->graphicsWrapper->drawElement(mesh->meshData->indices.size());

        for (const UPTR<ColorRendererComponent> &item : this->components)
            item->postDraw();
    }

    this->shaderManager->disableShader();
}

bool Renderer::contains(MeshComponent *mesh)
{
    bool result = false;

    for (MeshComponent *item : this->meshes)
    {
        if (item == mesh)
        {
            result = true;
            break;
        }
    }

    return result;
}

bool Renderer::fitsWithMesh(MeshComponent *mesh)
{
    Material *material = mesh->getMaterial();
    return
    (
        (this->componentsBitset == material->componentsBitset) &&
        ((this->shaderSetupItems.count(typeid(LightRendererShaderSetup).name()) > 0) == material->receivesLight) &&
        ((this->shaderSetupItems.count(typeid(ShadowRendererShaderSetup).name()) > 0) == material->receivesShadow)
    );
}

void Renderer::removeDestroyedEntities()
{
    std::list<MeshComponent *>::iterator it;

    for (it = this->meshes.begin(); it != this->meshes.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it));
            it = this->meshes.erase(it);
        }
        else
            ++it;
    }
}

} // namespace
