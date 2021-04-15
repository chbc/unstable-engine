#include "DOFRendererComponent.h"
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
	// ### USAR ESSE
	// https://developer.nvidia.com/gpugems/gpugems/part-iv-image-processing/chapter-23-depth-field-survey-techniques
DOFRendererComponent::DOFRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->shader = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(shader, ShaderVariables::SCREEN_TEXTURE);
	this->shaderManager->setupUniformLocation(shader, "depthMap");
	this->shaderManager->setupUniformLocation(shader, "focusNear");
	this->shaderManager->setupUniformLocation(shader, "focusFar");

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
	uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

	glm::vec2 pixelSize(width, height);
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->resolve<MultimediaManager>()->getNormalizedSize(pixelSize);

	GUIMeshData* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<GUIMeshData>{ quad };

	this->graphicsWrapper->createGUIVAO(quad, 0, false);
	this->graphicsWrapper->createGUIEBO(quad, 0, false);

	TextureManager* textureManager = singletonsManager->resolve<TextureManager>();
	Texture* texture = textureManager->createEmptyTexture(width, height);
	this->initialPassTextureId = texture->getId();
	
	texture = textureManager->createEmptyTexture(width, height);
	this->depthTextureId = texture->getId();

	std::vector<uint32_t> textureIds = { this->initialPassTextureId, this->depthTextureId };
	this->fbo = this->graphicsWrapper->generateColorFrameBuffer(textureIds, width, height);
}

void DOFRendererComponent::onPreRender()
{
	this->graphicsWrapper->bindFrameBuffer(this->fbo);
}

void DOFRendererComponent::onPostRender()
{
	this->graphicsWrapper->bindFrameBuffer(0);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->shader);
	this->shaderManager->setInt(this->shader, ShaderVariables::SCREEN_TEXTURE, 0);
	this->shaderManager->setInt(this->shader, "depthMap", 1);
	this->shaderManager->setFloat(this->shader, "focusNear", 10.0f);
	this->shaderManager->setFloat(this->shader, "focusFar", 15.0f);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->initialPassTextureId);
	this->graphicsWrapper->activateDiffuseTexture(this->depthTextureId);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
