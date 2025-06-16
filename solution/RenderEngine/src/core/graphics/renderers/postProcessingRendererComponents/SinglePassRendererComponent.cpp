#include "SinglePassRendererComponent.h"

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

SinglePassRendererComponent::SinglePassRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->program = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::SCREEN_TEXTURE);

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
	uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

	glm::vec2 pixelSize(width, height);
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->get<MultimediaManager>()->getNormalizedSize(pixelSize);

	MeshData2D* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<MeshData2D>{ quad };

	this->graphicsWrapper->createBuffers(quad, 0, false);

	TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
	Texture* texture = textureCreator->createEmptyTexture(width, height);
	this->textureId = texture->getId();

	this->firstPassFBO = this->graphicsWrapper->generateColorFrameBuffer(
		std::vector<uint32_t>{this->textureId}, texture->getWidth(), texture->getHeight()
	);
}

void SinglePassRendererComponent::onPostRender(uint32_t targetFBO)
{
	this->graphicsWrapper->bindFrameBuffer(targetFBO);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->program);
	this->shaderManager->setInt(this->program, ShaderVariables::SCREEN_TEXTURE, ETextureMap::GUI);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->textureId);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
