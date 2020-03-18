#include "BloomRendererComponent.h"

#include "SingletonsManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "PrimitiveMeshFactory.h"
#include "PostProcessingComponent.h"

namespace sre
{

BloomRendererComponent::BloomRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->blurShader = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(this->blurShader, ShaderVariables::SCREEN_TEXTURE);
	this->combineShader = this->shaderManager->loadFinalPassPostProcessingShader(component);

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(multimediaManager->getScreenWidth());
	uint32_t height = static_cast<uint32_t>(multimediaManager->getScreenHeight());

	glm::vec2 pixelSize{ width, height };
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->resolve<MultimediaManager>()->getNormalizedSize(pixelSize);

	GUIMeshData* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<GUIMeshData>{ quad };

	this->graphicsWrapper->createGUIVAO(quad, 0, false);
	this->graphicsWrapper->createGUIEBO(quad, 0, false);

	TextureManager* textureManager = singletonsManager->resolve<TextureManager>();
	Texture* texture = textureManager->createEmptyTexture(width, height);
	this->initialPassTextureId = texture->getId();

	texture = textureManager->createEmptyTexture(width, height);
	this->brightnessTextureId = texture->getId();

	texture = textureManager->createEmptyTexture(width, height);
	this->blurTextureIds[0] = texture->getId();

	texture = textureManager->createEmptyTexture(width, height);
	this->blurTextureIds[1] = texture->getId();

	std::vector<uint32_t> textureIds = { this->initialPassTextureId, this->brightnessTextureId };

	this->initialPassFBO = this->graphicsWrapper->generateColorFrameBuffer(textureIds, width, height);
	this->brightnessFBOs[0] = this->graphicsWrapper->generateColorFrameBuffer(std::vector<uint32_t>{ this->blurTextureIds[0] }, width, height);
	this->brightnessFBOs[1] = this->graphicsWrapper->generateColorFrameBuffer(std::vector<uint32_t>{ this->blurTextureIds[1] }, width, height);
}

void BloomRendererComponent::onPreRender()
{
	this->graphicsWrapper->bindFrameBuffer(this->initialPassFBO);
}

void BloomRendererComponent::onPostRender()
{
	// BLUR
	bool firstIteration = true;
	uint32_t horizontal = 1;
	this->graphicsWrapper->bindFrameBuffer(0);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->blurShader);
	this->shaderManager->setInt(this->blurShader, ShaderVariables::SCREEN_TEXTURE, 0);

	for (uint32_t i = 0; i < this->blurInteractionsCount; i++)
	{
		this->graphicsWrapper->bindFrameBuffer(this->brightnessFBOs[horizontal]);
		this->shaderManager->setInt(this->blurShader, "horizontal", horizontal);
		uint32_t textureId = firstIteration ? this->brightnessTextureId : this->blurTextureIds[!horizontal];
		
		this->graphicsWrapper->activateGUITexture(textureId);

		this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
		this->graphicsWrapper->enablePostProcessingSettings();
		this->graphicsWrapper->drawElement(this->meshData->indices.size());

		horizontal = !horizontal;
		if (firstIteration)
			firstIteration = false;
	}

	// COMBINE
	this->graphicsWrapper->bindFrameBuffer(0);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->combineShader);
	this->shaderManager->setInt(this->combineShader, ShaderVariables::SCREEN_TEXTURE, 0);
	this->shaderManager->setInt(this->combineShader, "bloom", 1);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->initialPassTextureId);
	this->graphicsWrapper->activateDiffuseTexture(this->blurTextureIds[0]);

	this->graphicsWrapper->drawElement(this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace