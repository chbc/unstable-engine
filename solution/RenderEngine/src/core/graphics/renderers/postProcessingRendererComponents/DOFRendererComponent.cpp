#include "DOFRendererComponent.h"
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
	// ### USAR ESSE
	// https://developer.nvidia.com/gpugems/gpugems/part-iv-image-processing/chapter-23-depth-field-survey-techniques
DOFRendererComponent::DOFRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->program = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::SCREEN_TEXTURE);
	this->shaderManager->setupUniformLocation(program, "depthMap");
	this->shaderManager->setupUniformLocation(program, "focusNear");
	this->shaderManager->setupUniformLocation(program, "focusFar");

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
	this->initialPassTextureId = texture->getId();
	
	texture = textureCreator->createEmptyTexture(width, height);
	this->depthTextureId = texture->getId();

	std::vector<uint32_t> textureIds = { this->initialPassTextureId, this->depthTextureId };
	this->firstPassFBO = this->graphicsWrapper->generateColorFrameBuffer(textureIds, width, height);
}

void DOFRendererComponent::onPostRender(uint32_t targetFBO)
{
	this->graphicsWrapper->bindFrameBuffer(targetFBO);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->program);
	this->shaderManager->setInt(this->program, ShaderVariables::SCREEN_TEXTURE, 0);
	this->shaderManager->setInt(this->program, "depthMap", 1);
	this->shaderManager->setFloat(this->program, "focusNear", 10.0f);
	this->shaderManager->setFloat(this->program, "focusFar", 15.0f);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->initialPassTextureId);
	this->graphicsWrapper->activateDiffuseTexture(this->depthTextureId);

	this->graphicsWrapper->drawElement(this->meshData->ebo, this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
