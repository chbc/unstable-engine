#include "CustomRenderer.h"
#include "MeshComponent.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "CustomMaterial.h"
#include "CustomMaterialComponent.h"
#include "Texture.h"

namespace sre
{

CustomRenderer::CustomRenderer(ABaseMaterial* arg_material, ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWeapper)
	: ABaseRenderer(arg_shaderManager, arg_graphicsWeapper)
{
	this->material = static_cast<CustomMaterial*>(arg_material);
}

void CustomRenderer::init()
{
	this->program = this->shaderManager->loadCustomShader(this->material->getShaderFilePaths());
	this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::VIEW_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::PROJECTION_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MODEL_MATRIX);

	this->initTextures();
}

void CustomRenderer::initTextures()
{
	if (this->material->hasComponent<CustomMaterialComponent>())
	{
		this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_TEXTURE_COORDS);

		CustomMaterialComponent* materialComponent = this->material->getComponent<CustomMaterialComponent>();
		this->texturesMap = materialComponent->getTexturesMap();

		for (const auto& item : this->texturesMap)
		{
			this->shaderManager->setupUniformLocation(this->program, item.first.c_str());
		}
	}
}

void CustomRenderer::render(CameraComponent* camera)
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
			// Matrix setup
			TransformComponent* transform = item->getTransform();
			const glm::mat4& modelMatrix = transform->getMatrix();
			this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

			MeshData* meshData = item->mesh;
			this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);

			item->notifyRenderAction(this->graphicsWrapper, this->shaderManager, this->program);
			this->graphicsWrapper->enableVertexPositions();

			this->graphicsWrapper->setLineWidth(item->lineWidth);
			this->graphicsWrapper->setPointSize(item->pointSize);

			EDrawMode::Type drawMode = item->getDrawMode();
			if (drawMode == EDrawMode::LINES_AND_POINTS)
			{
				this->graphicsWrapper->drawElement(meshData->ebo, meshData->indices.size(), EDrawMode::LINES);

				this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);
				this->graphicsWrapper->drawElement(meshData->ebo, meshData->indices.size(), EDrawMode::POINTS);
			}
			else
			{
				this->graphicsWrapper->drawElement(meshData->ebo, meshData->indices.size(), drawMode);
			}

			this->graphicsWrapper->setLineWidth(1.0f);
			this->graphicsWrapper->setPointSize(1.0f);
		}
	}

	this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_POSITION);
	this->shaderManager->disableShader();
}

void CustomRenderer::setupTextures()
{
	if (!this->texturesMap.empty())
	{
		this->graphicsWrapper->enableTexCoords();

		for (const auto& item : this->texturesMap)
		{
			Texture* texture = item.second;
			ETextureMap::Type textureMap = texture->getMapType();
			this->graphicsWrapper->activateTexture(texture->getId(), textureMap);
			this->shaderManager->setInt(this->program, item.first.c_str(), textureMap);
		}
	}
}

} // namespace
