#include "OutlineRendererPPComponent.h"

#include "SingletonsManager.h"
#include "TextureCreator.h"
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

	this->outlineProgram = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(this->outlineProgram, ShaderVariables::SCREEN_TEXTURE);
	
	this->combineProgram = this->shaderManager->loadFinalPassPostProcessingShader(component);

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
	uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

	glm::vec2 pixelSize{ width, height };
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->get<MultimediaManager>()->getNormalizedSize(pixelSize);

	MeshData2D* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<MeshData2D>{ quad };

	this->graphicsWrapper->createBuffers(quad, 0, false);

	TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
	Texture* texture = textureCreator->createEmptyTexture(width, height);
	this->initialPassTextureId = texture->getId();

	texture = textureCreator->createEmptyTexture(width, height);
	this->colorSourceTextureId = texture->getId();

	texture = textureCreator->createEmptyTexture(width, height);
	this->outlineTextureId = texture->getId();

	std::vector<uint32_t> textureIds = { this->initialPassTextureId, this->colorSourceTextureId };

	this->firstPassFBO = this->graphicsWrapper->generateColorFrameBuffer(textureIds, width, height);
	this->outlinePassFBO = this->graphicsWrapper->generateColorFrameBuffer(std::vector<uint32_t>{ this->outlineTextureId }, width, height);
}

void OutlineRendererPPComponent::onPostRender(uint32_t targetFBO)
{
	// OUTLINE
	this->shaderManager->enableShader(this->outlineProgram);
	this->shaderManager->setInt(this->outlineProgram, ShaderVariables::SCREEN_TEXTURE, 0);

	this->graphicsWrapper->bindFrameBuffer(this->outlinePassFBO);
	this->graphicsWrapper->activateGUITexture(this->outlineTextureId);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	// COMBINE
	this->graphicsWrapper->bindFrameBuffer(targetFBO);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->combineProgram);
	this->shaderManager->setInt(this->combineProgram, ShaderVariables::SCREEN_TEXTURE, 0);
	this->shaderManager->setInt(this->combineProgram, "brightnessTexture", 1);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->initialPassTextureId);
	this->graphicsWrapper->activateDiffuseTexture(this->outlineTextureId);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
