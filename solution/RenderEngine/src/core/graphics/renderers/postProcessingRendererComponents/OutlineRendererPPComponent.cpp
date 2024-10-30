#include "OutlineRendererPPComponent.h"

#include "SingletonsManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "PrimitiveMeshFactory.h"
#include "PostProcessingComponent.h"
#include "EngineValues.h"

namespace sre
{

OutlineRendererPPComponent::OutlineRendererPPComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->outlineShader = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(this->outlineShader, ShaderVariables::SCREEN_TEXTURE);
	
	this->combineShader = this->shaderManager->loadFinalPassPostProcessingShader(component);

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
	uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

	glm::vec2 pixelSize{ width, height };
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->get<MultimediaManager>()->getNormalizedSize(pixelSize);

	GUIMeshData* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<GUIMeshData>{ quad };

	this->graphicsWrapper->createGUIVAO(quad, 0, false);
	this->graphicsWrapper->createGUIEBO(quad, 0, false);

	TextureManager* textureManager = singletonsManager->get<TextureManager>();
	Texture* texture = textureManager->createEmptyTexture(width, height);
	this->initialPassTextureId = texture->getId();

	texture = textureManager->createEmptyTexture(width, height);
	this->colorSourceTextureId = texture->getId();

	texture = textureManager->createEmptyTexture(width, height);
	this->outlineTextureId = texture->getId();

	std::vector<uint32_t> textureIds = { this->initialPassTextureId, this->colorSourceTextureId };

	this->firstPassFBO = this->graphicsWrapper->generateColorFrameBuffer(textureIds, width, height);
	this->outlinePassFBO = this->graphicsWrapper->generateColorFrameBuffer(std::vector<uint32_t>{ this->outlineTextureId }, width, height);
}

void OutlineRendererPPComponent::onPostRender(uint32_t targetFBO)
{
	// OUTLINE
	this->shaderManager->enableShader(this->outlineShader);
	this->shaderManager->setInt(this->outlineShader, ShaderVariables::SCREEN_TEXTURE, 0);

	this->graphicsWrapper->bindFrameBuffer(this->outlinePassFBO);
	this->graphicsWrapper->activateGUITexture(this->outlineTextureId);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	// COMBINE
	this->graphicsWrapper->bindFrameBuffer(targetFBO);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->combineShader);
	this->shaderManager->setInt(this->combineShader, ShaderVariables::SCREEN_TEXTURE, 0);
	this->shaderManager->setInt(this->combineShader, "brightnessTexture", 1);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->initialPassTextureId);
	this->graphicsWrapper->activateDiffuseTexture(this->outlineTextureId);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
