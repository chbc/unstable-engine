#include "BloomRendererComponent.h"

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

BloomRendererComponent::BloomRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->blurProgram = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(this->blurProgram, ShaderVariables::SCREEN_TEXTURE);
	this->shaderManager->setupUniformLocation(this->blurProgram, "horizontal");
	this->shaderManager->setupUniformLocation(this->blurProgram, "textureSize");
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
	this->brightnessTextureId = texture->getId();

	texture = textureCreator->createEmptyTexture(width, height);
	this->blurTextureIds[0] = texture->getId();

	texture = textureCreator->createEmptyTexture(width, height);
	this->blurTextureIds[1] = texture->getId();

	std::vector<uint32_t> textureIds = { this->initialPassTextureId, this->brightnessTextureId };

	this->firstPassFBO = this->graphicsWrapper->generateColorFrameBuffer(textureIds, width, height);
	this->blurFBOs[0] = this->graphicsWrapper->generateColorFrameBuffer(std::vector<uint32_t>{ this->blurTextureIds[0] }, width, height);
	this->blurFBOs[1] = this->graphicsWrapper->generateColorFrameBuffer(std::vector<uint32_t>{ this->blurTextureIds[1] }, width, height);
}

void BloomRendererComponent::onPostRender(uint32_t targetFBO)
{
	// BLUR
	bool firstIteration = true;
	uint32_t horizontal = 1;
	this->shaderManager->enableShader(this->blurProgram);
	this->shaderManager->setInt(this->blurProgram, ShaderVariables::SCREEN_TEXTURE, 0);

	// ###
	float textureSize[2] = { 1024 * 0.25f, 728 * 0.25f};
	
	for (uint32_t i = 0; i < this->blurInteractionsCount; i++)
	{
		this->graphicsWrapper->bindFrameBuffer(this->blurFBOs[horizontal]);
		this->shaderManager->setInt(this->blurProgram, "horizontal", horizontal);
		this->shaderManager->setVec2(this->blurProgram, "textureSize", textureSize);
		uint32_t textureId = firstIteration ? this->brightnessTextureId : this->blurTextureIds[!horizontal];
		
		this->graphicsWrapper->activateTexture(textureId, ETextureMap::GUI);

		this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
		this->graphicsWrapper->enablePostProcessingSettings();
		this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

		horizontal = !horizontal;
		if (firstIteration)
			firstIteration = false;

		if (i == 6)
		{
			textureSize[0] = 1024 * 0.5f;
			textureSize[1] = 728 * 0.5f;
		}
		else if (i == 8)
		{
			textureSize[0] = 1024;
			textureSize[1] = 728;
		}
	}

	// COMBINE
	this->graphicsWrapper->bindFrameBuffer(targetFBO);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->combineProgram);
	this->shaderManager->setInt(this->combineProgram, ShaderVariables::SCREEN_TEXTURE, 0);
	this->shaderManager->setInt(this->combineProgram, "bloom", 1);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateTexture(this->initialPassTextureId, ETextureMap::GUI);
	this->graphicsWrapper->activateTexture(this->blurTextureIds[0], ETextureMap::DIFFUSE);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
