#include "SkyboxRenderer.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "SkyboxComponent.h"
#include "Entity.h"
#include "CustomMaterial.h"
#include "CustomMaterialComponent.h"
#include "Texture.h"

namespace sre
{

SkyboxRenderer::SkyboxRenderer(class ABaseMaterial* arg_material, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWrapper)
	: CustomRenderer(arg_material, arg_shaderManager, arg_graphicsWrapper)
{
}

void SkyboxRenderer::init()
{
	this->program = this->shaderManager->loadCustomShader(this->material->getShaderFilePaths());
	this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::VIEW_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::PROJECTION_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::SKYBOX_MAP);

	this->initTextures();
}

void SkyboxRenderer::initTextures()
{
	if (this->material->hasComponent<CustomMaterialComponent>())
	{
		CustomMaterialComponent* materialComponent = this->material->getComponent<CustomMaterialComponent>();
		this->texturesMap = materialComponent->getTexturesMap();

		for (const auto& item : this->texturesMap)
		{
			this->shaderManager->setupUniformLocation(this->program, item.first.c_str());
		}
	}
}

void SkyboxRenderer::render(CameraComponent* camera)
{
	this->shaderManager->enableShader(this->program);

	const glm::mat4& viewMatrix = camera->getViewMatrix();
	const glm::mat4& projectionMatrix = camera->getProjectionMatrix();

	this->shaderManager->setMat4(this->program, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
	this->shaderManager->setMat4(this->program, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);

	this->setupTextures();

	for (MeshComponent* item : this->meshComponents)
	{
		if (item->isEnabled() && item->getEntity()->isEnabled())
		{
			MeshData* meshData = item->mesh;
			this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);

			item->notifyRenderAction(this->graphicsWrapper, this->shaderManager, this->program);
			this->graphicsWrapper->enableVertexPositions();

			EDrawMode::Type drawMode = item->getDrawMode();
			this->graphicsWrapper->drawElement(meshData->ebo, meshData->indices.size(), drawMode);
		}
	}

	this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_POSITION);
	this->shaderManager->disableShader();
}

void SkyboxRenderer::setupTextures()
{
	for (const auto& item : this->texturesMap)
	{
		Texture* texture = item.second;
		ETextureMap::Type textureMap = texture->getMapType();
		this->graphicsWrapper->activateCubeMapTexture(texture->getId(), textureMap);
		this->shaderManager->setInt(this->program, item.first.c_str(), textureMap);
	}
}

} // namespace
