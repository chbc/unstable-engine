#include "GUIRenderer.h"

#include "Entity.h"
#include "GUIImageComponent.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "Texture.h"

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

	GUIMeshData* meshData = static_cast<GUIMeshData*>(guiComponent->meshData.get());
    this->graphicsWrapper->createGUIVAO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
    this->graphicsWrapper->createGUIEBO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
}

void GUIRenderer::addDynamicGUIComponent(GUIImageComponent *guiComponent)
{
    this->dynamicGUIComponents.push_back(guiComponent);
	
	GUIMeshData* meshData = static_cast<GUIMeshData*>(guiComponent->meshData.get());
	this->graphicsWrapper->createGUIVAO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
	this->graphicsWrapper->createGUIEBO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
}

void GUIRenderer::render()
{
    this->shaderManager->enableShader(this->shader);
    this->shaderManager->setInt(this->shader, ShaderVariables::GUI_TEXTURE, EMaterialMap::GUI);

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

    this->graphicsWrapper->bindVAO(guiComponent->meshData->vao, guiComponent->meshData->vbo);
    this->graphicsWrapper->enableGUISettings();
    this->graphicsWrapper->activateGUITexture(guiComponent->getTextureId());
}

void GUIRenderer::removeDestroyedEntities()
{
    std::list<GUIImageComponent *>::iterator it;

    for (it = this->guiComponents.begin(); it != this->guiComponents.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it)->meshData.get());
            it = this->guiComponents.erase(it);
        }
        else
            ++it;
    }
}

} // namespace
