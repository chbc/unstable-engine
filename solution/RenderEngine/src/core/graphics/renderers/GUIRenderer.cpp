#include "GUIRenderer.h"

#include "Entity.h"
#include "GUIImageComponent.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "Texture.h"

namespace sre
{

GUIRenderer::~GUIRenderer()
{
    for (GUIImageComponent*item : this->guiComponents)
        this->graphicsWrapper->deleteBuffers(item->mesh->meshData.get());

    for (GUIImageComponent* item : this->dynamicGuiComponents)
        this->graphicsWrapper->deleteBuffers(item->mesh->meshData.get());

    this->guiComponents.clear();
    this->dynamicGuiComponents.clear();

    this->shaderManager->releaseShader(this->shader);
}

GUIRenderer::GUIRenderer(ShaderManager *arg_shaderManager, AGraphicsWrapper *arg_graphicsWrapper) 
    : shaderManager(arg_shaderManager), graphicsWrapper(arg_graphicsWrapper)
{
}

void GUIRenderer::loadShader()
{
    this->shader = this->shaderManager->loadGUIShader();

    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::GUI_TEXTURE);
    this->shaderManager->setupUniformLocation(this->shader, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupAttributeLocation(this->shader, ShaderVariables::IN_POSITION);
    this->shaderManager->setupAttributeLocation(this->shader, ShaderVariables::IN_TEXTURE_COORDS);
}

void GUIRenderer::addGUIComponent(GUIImageComponent *guiComponent)
{
    this->guiComponents.push_back(guiComponent);

	GUIMeshData* meshData = static_cast<GUIMeshData*>(guiComponent->mesh->meshData.get());
    this->graphicsWrapper->createGUIVAO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
    this->graphicsWrapper->createGUIEBO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
}

void GUIRenderer::addDynamicGUIComponent(GUIImageComponent *guiComponent)
{
    this->dynamicGuiComponents.push_back(guiComponent);
	
	GUIMeshData* meshData = static_cast<GUIMeshData*>(guiComponent->mesh->meshData.get());
	this->graphicsWrapper->createGUIVAO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
	this->graphicsWrapper->createGUIEBO(meshData, guiComponent->maxItems, guiComponent->isDynamic);
}

void GUIRenderer::render()
{
    this->shaderManager->enableShader(this->shader);
    this->shaderManager->setInt(this->shader, ShaderVariables::GUI_TEXTURE, EMaterialMap::GUI);

    this->graphicsWrapper->disableDepthTest();

    // Static meshes
    for (GUIImageComponent *item : this->guiComponents)
    {
        if (item->getEntity()->isEnabled())
        {
            this->setup(item);
            this->graphicsWrapper->drawElement(item->mesh->meshData->ebo, item->mesh->meshData->indices.size());
        }
    }

    // Dynamic meshes
    for (GUIImageComponent *item : this->dynamicGuiComponents)
    {
        if ((item->mesh->meshData.get() != nullptr) && item->getEntity()->isEnabled())
        {
            this->setup(item);
            this->graphicsWrapper->drawElement(item->mesh->meshData->ebo, item->mesh->meshData->indices.size());
        }
    }

    this->graphicsWrapper->enableDepthTest();

    this->shaderManager->disableVertexAttribute(this->shader, ShaderVariables::IN_TEXTURE_COORDS);
    this->shaderManager->disableShader();
}

void GUIRenderer::setup(GUIImageComponent *guiComponent)
{
    // Matrix setup
    TransformComponent *transform = guiComponent->getTransform();
    glm::mat4 modelMatrix = transform->getMatrix();
    this->shaderManager->setMat4(this->shader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

    this->graphicsWrapper->bindVAO(guiComponent->mesh->meshData->vao, guiComponent->mesh->meshData->vbo);
    this->shaderManager->setVertexAttributePointer(this->shader, ShaderVariables::IN_POSITION, 2, sizeof(GUIVertexData), GUIVertexData::getPositionOffset());
    this->shaderManager->setVertexAttributePointer(this->shader, ShaderVariables::IN_TEXTURE_COORDS, 2, sizeof(GUIVertexData), ABaseVertexData::getUVOffset());
    this->graphicsWrapper->activateGUITexture(guiComponent->getTextureId());
}

void GUIRenderer::removeDestroyedEntities()
{
    std::list<GUIImageComponent *>::iterator it;

    for (it = this->guiComponents.begin(); it != this->guiComponents.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it)->mesh->meshData.get());
            it = this->guiComponents.erase(it);
        }
        else
            ++it;
    }

    for (it = this->dynamicGuiComponents.begin(); it != this->dynamicGuiComponents.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it)->mesh->meshData.get());
            it = this->dynamicGuiComponents.erase(it);
        }
        else
            ++it;
    }
}

void GUIRenderer::clean()
{
    std::list<GUIImageComponent*>::iterator it;
    for (it = this->guiComponents.begin(); it != this->guiComponents.end(); )
    {
        this->graphicsWrapper->deleteBuffers((*it)->mesh->meshData.get());
        it = this->guiComponents.erase(it);
    }

    for (it = this->dynamicGuiComponents.begin(); it != this->dynamicGuiComponents.end(); )
    {
        this->graphicsWrapper->deleteBuffers((*it)->mesh->meshData.get());
        it = this->dynamicGuiComponents.erase(it);
    }
}

bool GUIRenderer::isEmpty()
{
    return (this->guiComponents.empty() && this->dynamicGuiComponents.empty());
}

} // namespace
