#include "GUIRenderer.h"

#include "Entity.h"
#include "GUIImageComponent.h"
#include "GUITextComponent.h"
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
    this->imageComponents.clear();
    this->textComponents.clear();

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

void GUIRenderer::addImageComponent(GUIImageComponent * imageComponent)
{
    this->imageComponents.push_back(imageComponent);

    this->graphicsWrapper->createBuffers(imageComponent->meshData, 1, false);
}

void GUIRenderer::addTextComponent(GUITextComponent* textComponent)
{
    this->textComponents.push_back(textComponent);
	
	MeshData2D* meshData = static_cast<MeshData2D*>(textComponent->meshData);
	this->graphicsWrapper->createBuffers(meshData, textComponent->maxItems, textComponent->isDynamic);
}

void GUIRenderer::render()
{
    this->shaderManager->enableShader(this->program);
    this->shaderManager->setInt(this->program, ShaderVariables::GUI_TEXTURE, ETextureMap::GUI);

    this->graphicsWrapper->disableDepthTest();

    // Static meshes
    for (GUIImageComponent *item : this->imageComponents)
    {
        if (item->isEnabled() && item->getEntity()->isEnabled())
        {
            this->setup(item);
            this->graphicsWrapper->drawElement(item->meshData->ebo, item->meshData->indices.size());
        }
    }

    // Text meshes
    for (GUITextComponent *item : this->textComponents)
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

void GUIRenderer::setup(ABaseGUIComponent* guiComponent)
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
    std::list<GUIImageComponent *>::iterator imageIt;

    for (imageIt = this->imageComponents.begin(); imageIt != this->imageComponents.end(); )
    {
        if (!(*imageIt)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*imageIt)->meshData);
            imageIt = this->imageComponents.erase(imageIt);
        }
        else
            ++imageIt;
    }

    std::list<GUITextComponent*>::iterator textIt;

    for (textIt = this->textComponents.begin(); textIt != this->textComponents.end(); )
    {
        if (!(*textIt)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*textIt)->meshData);
            textIt = this->textComponents.erase(textIt);
        }
        else
            ++textIt;
    }
}

bool GUIRenderer::isEmpty()
{
    return (this->imageComponents.empty() && this->textComponents.empty());
}

} // namespace
