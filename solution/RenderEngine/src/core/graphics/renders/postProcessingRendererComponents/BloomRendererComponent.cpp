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

	this->initialPassShader = this->shaderManager->loadInitialPassPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(initialPassShader, ShaderVariables::SCREEN_TEXTURE);

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
	this->finalPassTextureId = texture->getId();

	this->initialPassFBO = this->graphicsWrapper->generateColorFrameBuffer(this->initialPassTextureId, width, height);
	this->finalPassFBO = this->graphicsWrapper->generateColorFrameBuffer(this->initialPassTextureId, width, height);
}

void BloomRendererComponent::onPreRender()
{
	this->graphicsWrapper->bindFrameBuffer(this->initialPassFBO);
}

void BloomRendererComponent::onPostRender()
{
	this->graphicsWrapper->bindFrameBuffer(0);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->initialPassShader);
	this->shaderManager->setInt(this->initialPassShader, ShaderVariables::SCREEN_TEXTURE, EMaterialMap::GUI);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->initialPassTextureId);

	this->graphicsWrapper->drawElement(this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
