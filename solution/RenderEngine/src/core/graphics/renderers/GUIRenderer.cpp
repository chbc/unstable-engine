#include "GUIRenderer.h"

#include "Entity.h"
#include "GUIImageComponent.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "Texture.h"

namespace sre
{


GUIRenderer::GUIRenderer(ShaderManager *arg_shaderManager, AGraphicsWrapper *arg_graphicsWrapper) 
    : shaderManager(arg_shaderManager), graphicsWrapper(arg_graphicsWrapper)
{ }

GUIRenderer::~GUIRenderer()
{
    this->guiComponents.clear();
    this->dynamicGuiComponents.clear();

    this->shaderManager->releaseShader(this->program);
}

void GUIRenderer::loadShader()
{
    this->program = this->shaderManager->loadGUIShader();

    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::GUI_TEXTURE);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
    this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_TEXTURE_COORDS);
}

void GUIRenderer::addGUIComponent(GUIImageComponent *guiComponent)
{
    this->guiComponents.push_back(guiComponent);

    this->graphicsWrapper->createBuffers(guiComponent->meshData, guiComponent->maxItems, guiComponent->isDynamic);
}

void GUIRenderer::addDynamicGUIComponent(GUIImageComponent *guiComponent)
{
    this->dynamicGuiComponents.push_back(guiComponent);
	
	MeshData2D* meshData = static_cast<MeshData2D*>(guiComponent->meshData);
	this->graphicsWrapper->createBuffers(meshData, guiComponent->maxItems, guiComponent->isDynamic);
}

void GUIRenderer::render()
{
    this->shaderManager->enableShader(this->program);
    this->shaderManager->setInt(this->program, ShaderVariables::GUI_TEXTURE, ETextureMap::GUI);

    this->graphicsWrapper->disableDepthTest();

    // Static meshes
    for (GUIImageComponent *item : this->guiComponents)
    {
        if (item->getEntity()->isEnabled())
        {
            this->setup(item);
            this->graphicsWrapper->drawElement(item->meshData->ebo, item->meshData->indices.size());
        }
    }

    // Dynamic meshes
    for (GUIImageComponent *item : this->dynamicGuiComponents)
    {
        if ((item->meshData != nullptr) && item->getEntity()->isEnabled())
        {
            this->setup(item);
            this->graphicsWrapper->drawElement(item->meshData->ebo, item->meshData->indices.size());
        }
    }

    this->graphicsWrapper->enableDepthTest();

    this->shaderManager->disableVertexAttribute(this->program, ShaderVariables::IN_TEXTURE_COORDS);
    this->shaderManager->disableShader();
}

void GUIRenderer::setup(GUIImageComponent *guiComponent)
{
    // Matrix setup
    TransformComponent *transform = guiComponent->getTransform();
    glm::mat4 modelMatrix = transform->getMatrix();
    this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

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
            this->graphicsWrapper->deleteBuffers((*it)->meshData);
            it = this->guiComponents.erase(it);
        }
        else
            ++it;
    }

    for (it = this->dynamicGuiComponents.begin(); it != this->dynamicGuiComponents.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it)->meshData);
            it = this->dynamicGuiComponents.erase(it);
        }
        else
            ++it;
    }
}

bool GUIRenderer::isEmpty()
{
    return (this->guiComponents.empty() && this->dynamicGuiComponents.empty());
}

} // namespace
