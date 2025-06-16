#include "HDRRendererComponent.h"

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
	
HDRRendererComponent::HDRRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->shader = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(shader, ShaderVariables::SCREEN_TEXTURE);
	this->shaderManager->setupUniformLocation(this->shader, "exposure");
	this->shaderManager->setupUniformLocation(this->shader, "enabled");

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
	uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

	glm::vec2 pixelSize(width, height);
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->get<MultimediaManager>()->getNormalizedSize(pixelSize);

	MeshData2D* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<MeshData2D>{ quad };

	this->graphicsWrapper->createBuffers(quad, 0, false);

	TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
	Texture* texture = textureCreator->createEmptyFloatingPointTexture(width, height);
	this->textureId = texture->getId();

	this->firstPassFBO = this->graphicsWrapper->generateColorFrameBuffer(
		std::vector<uint32_t>{this->textureId}, width, height
	);

	this->effect = component->getEffect(PPE::HDR);
	this->effect->setValue("exposure", 0.5f);
	this->effect->setValue("enabled", 0.0f);
}

void HDRRendererComponent::onPostRender(uint32_t targetFBO)
{
	this->graphicsWrapper->bindFrameBuffer(targetFBO);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->shader);
	this->shaderManager->setInt(this->shader, ShaderVariables::SCREEN_TEXTURE, ETextureMap::GUI);
	this->shaderManager->setFloat(this->shader, "exposure", this->effect->getValue("exposure"));
	this->shaderManager->setFloat(this->shader, "enabled", this->effect->getValue("enabled"));

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->textureId);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
