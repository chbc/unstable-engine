#include "SkyboxRenderer.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "Entity.h"
#include "CustomMaterial.h"
#include "CustomMaterialComponent.h"
#include "Texture.h"
#include "LightManager.h"

#include "OpenGLAPI.h"

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

	this->initTextures();
}

void SkyboxRenderer::initTextures()
{
	if (this->material->hasComponent<CustomMaterialComponent>())
	{
		CustomMaterialComponent* materialComponent = this->material->getComponent<CustomMaterialComponent>();
		std::unordered_map<std::string, Texture*> inputTexturesMap = materialComponent->getTexturesMap();
		std::unordered_map<ETextureMap::Type, Texture*> iblTexturesMap;

		for (const auto& item : inputTexturesMap)
		{
			if (item.second->getMapType() == ETextureMap::SKYBOX)
			{
				this->texturesMap[item.first] = item.second;
				this->shaderManager->setupUniformLocation(this->program, item.first.c_str());
			}
			else
			{
				iblTexturesMap[item.second->getMapType()] = item.second;
			}
		}

		LightManager* lightManager = SingletonsManager::getInstance()->get<LightManager>();
		lightManager->loadIBL(iblTexturesMap);
	}
}

void SkyboxRenderer::render(CameraComponent* camera)
{
	this->shaderManager->enableShader(this->program);

	this->setupTextures();

	this->graphicsWrapper->enableCubemapSettings();

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

	this->graphicsWrapper->disableCubemapSettings();
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

void SkyboxRenderer::reloadMaterial(ABaseMaterial* newMaterial)
{
	this->material = static_cast<CustomMaterial*>(newMaterial);
	this->initTextures();
}

} // namespace
