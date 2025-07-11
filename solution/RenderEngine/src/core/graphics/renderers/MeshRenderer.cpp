#include "MeshRenderer.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "Material.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "LightManager.h"
#include "AssetsManager.h"

#include "LightRendererShaderSetup.h"
#include "LitRendererComponent.h"
#include "NormalRendererComponent.h"
#include "SpecularRendererComponent.h"
#include "AORendererComponent.h"
#include "OutlineRendererComponent.h"
#include "SpriteRendererComponent.h"
#include "PBRRendererComponent.h"

namespace sre
{

MeshRenderer::MeshRenderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ABaseRenderer(shaderManager, graphicsWrapper)
{
    LightManager * lightManager = SingletonsManager::getInstance()->get<LightManager>();

    // ### COLOCAR NUM FACTORY
    for (std::size_t i = EComponentId::COLOR_MATERIAL; i < EComponentId::SIZE; i++)
    {
        if (material->componentsBitset[i])
        {
            switch (i)
            {
                case EComponentId::COLOR_MATERIAL:
                    this->addComponent<ColorRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::LIT_MATERIAL:
                    this->addComponent<LitRendererComponent>(this->shaderManager, this->graphicsWrapper, lightManager->hasAnyLight());
                    break;
                case EComponentId::DIFFUSE_MATERIAL:
                    this->addComponent<DiffuseRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::NORMAL_MATERIAL:
                    this->addComponent<NormalRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::SPECULAR_MATERIAL:
                    this->addComponent<SpecularRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::AO_MATERIAL:
                    this->addComponent<AORendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
				case EComponentId::PBR_MATERIAL:
					this->addComponent<PBRRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::SECOND_TARGET_COLOR_MATERIAL:
                    this->addComponent<OutlineRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                case EComponentId::SPRITE_MATERIAL:
                    this->addComponent<SpriteRendererComponent>(this->shaderManager, this->graphicsWrapper);
                    break;
                default: break;
            }

            this->componentsBitset[i] = true;
        }
    }
}

MeshRenderer::~MeshRenderer()
{
    this->shaderManager->releaseShader(this->program);
}

void MeshRenderer::init(bool useBrightnessSegmentation, bool includeDepth)
{
    this->loadShaderSetupItems();
    this->loadShader(useBrightnessSegmentation, includeDepth);

    for (const auto &item : this->shaderSetupItems)
        item.second->onSceneLoaded(this->program);

    for (const auto &item : this->componentsMap)
        item.second->onSceneLoaded(this->program);
}

void MeshRenderer::loadShaderSetupItems()
{
    BaseRendererShaderSetup *item = new BaseRendererShaderSetup(this->shaderManager, this->graphicsWrapper);
    this->shaderSetupItems[typeid(BaseRendererShaderSetup).name()] = UPTR<BaseRendererShaderSetup>(item);

    LightManager *lightManager = SingletonsManager::getInstance()->get<LightManager>();
    if (this->hasComponent<LitRendererComponent>())
    {
		if (lightManager->hasAnyLight())
		{
			item = new LightRendererShaderSetup(this->shaderManager, this->graphicsWrapper);
			this->shaderSetupItems[typeid(LightRendererShaderSetup).name()] = UPTR<BaseRendererShaderSetup>(item);

			this->lightData.receivesLight = true;
			this->lightData.directionalLightsCount = lightManager->directionalLights.size();
			this->lightData.pointLightsCount = lightManager->pointLights.size();
			this->lightData.hasAnyShadowCaster = lightManager->hasAnyShadowCaster();

			if (this->lightData.hasAnyShadowCaster)
			{
				item = new ShadowRendererShaderSetup(this->shaderManager, this->graphicsWrapper);
				this->shaderSetupItems[typeid(ShadowRendererShaderSetup).name()] = UPTR<BaseRendererShaderSetup>(item);
			}
		}
		else
		{
			this->removeComponent<LitRendererComponent>();
			this->removeComponent<NormalRendererComponent>();
			this->removeComponent<SpecularRendererComponent>();
		}
    }
}

void MeshRenderer::loadShader(bool useBrightnessSegmentation, bool includeDepth)
{
    this->program = this->shaderManager->loadShader(
		this->componentsBitset, this->lightData, useBrightnessSegmentation, includeDepth
	);
}

void MeshRenderer::render()
{
    // Shader setup
    this->shaderManager->enableShader(this->program);

    for (const auto &item : this->shaderSetupItems)
        item.second->setupShaderValues(this->program);

    for (MeshComponent *meshComponent : this->meshComponents)
    {
        if (meshComponent->getEntity()->isEnabled())
        {
            // Matrix setup
            TransformComponent* transform = meshComponent->getTransform();
            const glm::mat4& modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            MeshData* meshData = meshComponent->mesh;
            this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);
            for (const auto& item : this->componentsMap)
            {
                item.second->setupShaderValues(meshComponent, this->program);
                item.second->preDraw(this->program);
            }

            meshComponent->notifyRenderAction(this->shaderManager, this->program);
            this->graphicsWrapper->drawElement(meshData->ebo, meshData->indices.size(), meshComponent->getDrawMode());
        }
    }

    for (const auto &item : this->componentsMap)
        item.second->postDraw(this->program);

    this->shaderManager->disableShader();
}

bool MeshRenderer::fitsWithMaterial(Material* material)
{
    return (this->componentsBitset == material->componentsBitset);
}

} // namespace
