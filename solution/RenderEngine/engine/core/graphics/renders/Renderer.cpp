#include "Renderer.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/core/graphics/MatrixManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/graphics/LightManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>

namespace sre
{

Renderer::Renderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
    
    for (int i = 0; i <= EMaterialMap::SIZE; i++)
    {
        if (material->componentsBitset[i])
        {
            switch (i)
            {
                case EMaterialMap::COLOR:
                    this->addComponent<ColorRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EMaterialMap::DIFFUSE:
                    this->addComponent<DiffuseRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EMaterialMap::NORMAL:
                    this->addComponent<NormalRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EMaterialMap::SPECULAR:
                    this->addComponent<SpecularRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EMaterialMap::AMBIENT_OCCLUSION:
                    this->addComponent<AORendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                default: break;
            }
        }
    }
}

Renderer::~Renderer()
{
    for (MeshComponent *item : this->meshes)
        this->graphicsWrapper->deleteBuffers(item);
}

void Renderer::loadShader()
{
    this->shader = this->shaderManager->loadShader(this->componentsBitset);
    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::PROJECTION_MATRIX);
    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::CAMERA_POSITION);
    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::MODEL_MATRIX);

    for (const UPTR<ColorRendererComponent> &item : this->components)
    {
        item->onLoadShader(this->shader);
    }
}

void Renderer::addMesh(MeshComponent *mesh)
{
    this->meshes.push_back(mesh);
    this->graphicsWrapper->createVAO(mesh);
    this->graphicsWrapper->createEBO(mesh);
}

void Renderer::render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition)
{
    // Shader setup
    this->shaderManager->enableShader(this->shader);

    glm::mat4 viewMatrix = matrixManager->getViewMatrix();
    glm::mat4 projectionMatrix = matrixManager->getProjectionMatrix();

    this->shaderManager->setMat4(this->shader, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
    this->shaderManager->setMat4(this->shader, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);
    this->shaderManager->setVec3(this->shader, ShaderVariables::CAMERA_POSITION, &cameraPosition[0]);

    lightManager->setupValues(this->shaderManager, this->shader);

    for (MeshComponent *mesh : this->meshes)
    {
        // Matrix setup
        TransformComponent *transform = mesh->getTransform();
        glm::mat4 modelMatrix = transform->getMatrix();
        this->shaderManager->setMat4(this->shader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

        this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
        for (const UPTR<ColorRendererComponent> &item : this->components)
        {
            item->setupShaderVariables(mesh, this->shader);
            item->preDraw();
        }

        this->graphicsWrapper->drawElement(mesh->objectData->indices.size());

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
    return (this->componentsBitset == mesh->getMaterial()->componentsBitset);
}

void Renderer::removeDestroyedEntities()
{
    this->meshes.remove_if([](MeshComponent *item) { return !item->getEntity()->isAlive(); });
}

} // namespace
