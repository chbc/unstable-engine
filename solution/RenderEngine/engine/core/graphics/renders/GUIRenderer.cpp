#include "GUIRenderer.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/renderables/gui/GUIImageComponent.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/core/graphics/MatrixManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/multimedia/textures/Texture.h>

namespace sre
{

GUIRenderer::GUIRenderer(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
}

void GUIRenderer::loadShader()
{
    this->shader = this->shaderManager->loadGUIShader();

    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::GUI_TEXTURE);
    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::MODEL_MATRIX);
}

void GUIRenderer::addGUIComponent(GUIImageComponent *guiComponent)
{
    this->guiComponents.push_back(guiComponent);
    this->graphicsWrapper->createGUIVAO(guiComponent);
    this->graphicsWrapper->createGUIEBO(guiComponent);
}

void GUIRenderer::addDynamicGUIComponent(GUIImageComponent *guiComponent)
{
    this->dynamicGUIComponents.push_back(guiComponent);
    this->graphicsWrapper->createGUIVAO(guiComponent);
    this->graphicsWrapper->createGUIEBO(guiComponent);
}

void GUIRenderer::render(MatrixManager *matrixManager)
{
    this->shaderManager->enableShader(this->shader);
    this->shaderManager->setInt(this->shader, ShaderVariables::GUI_TEXTURE, 0);

    // Static meshes
    for (GUIImageComponent *item : this->guiComponents)
    {
        this->setup(item);
        this->graphicsWrapper->drawElement(item->meshData->indices.size());
    }

    // Dynamic meshes
    for (GUIImageComponent *item : this->dynamicGUIComponents)
    {
        if (item->meshData.get() != nullptr)
        {
            this->setup(item);
            this->graphicsWrapper->drawElement(item->meshData->indices.size());
        }
    }

    this->graphicsWrapper->disableGUISettings();
    this->shaderManager->disableShader();
}

void GUIRenderer::setup(GUIImageComponent *guiComponent)
{
    // Matrix setup
    TransformComponent *transform = guiComponent->getTransform();
    glm::mat4 modelMatrix = transform->getMatrix();
    this->shaderManager->setMat4(this->shader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

    this->graphicsWrapper->bindVAO(guiComponent->vao, guiComponent->vbo);
    this->graphicsWrapper->enableGUISettings();
    this->graphicsWrapper->activeDiffuseTexture(guiComponent->getTextureId());
}

void GUIRenderer::removeDestroyedEntities()
{
    std::list<GUIImageComponent *>::iterator it;

    for (it = this->guiComponents.begin(); it != this->guiComponents.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it));
            it = this->guiComponents.erase(it);
        }
        else
            ++it;
    }
}

} // namespace
