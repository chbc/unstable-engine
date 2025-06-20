#include "MeshRenderer.h"

#include "Entity.h"
#include "MeshComponent.h"
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
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
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

void MeshRenderer::addMesh(MeshComponent * meshComponent)
{
    this->meshes.push_back(meshComponent);

    if (meshComponent->mesh->ebo == 0)
    {
        this->graphicsWrapper->createBuffers(meshComponent->mesh);
    }
}

void MeshRenderer::render()
{
    // Shader setup
    this->shaderManager->enableShader(this->program);

    for (const auto &item : this->shaderSetupItems)
        item.second->setupShaderValues(this->program);

    for (MeshComponent *mesh : this->meshes)
    {
        if (mesh->getEntity()->isEnabled())
        {
            // Matrix setup
            TransformComponent* transform = mesh->getTransform();
            glm::mat4 modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            MeshData* meshData = mesh->mesh;
            this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);
            for (const auto& item : this->componentsMap)
            {
                item.second->setupShaderValues(mesh, this->program);
                item.second->preDraw(this->program);
            }

            this->graphicsWrapper->drawElement(meshData->ebo, meshData->indices.size());
        }
    }

    for (const auto &item : this->componentsMap)
        item.second->postDraw(this->program);

    this->shaderManager->disableShader();
}

bool MeshRenderer::contains(MeshComponent *mesh)
{
    bool result = false;

    for (MeshComponent *item : this->meshes)
    {
        if (item == mesh)
        {
            result = true;
            break;
        }
    }

    return result;
}

bool MeshRenderer::fitsWithMaterial(Material* material)
{
    return (this->componentsBitset == material->componentsBitset);
}

void MeshRenderer::removeDestroyedEntities()
{
    std::list<MeshComponent *>::iterator it;

    for (it = this->meshes.begin(); it != this->meshes.end(); )
    {
        MeshComponent* item = *it;
        if (!item->getEntity()->isAlive())
        {
            it = this->meshes.erase(it);
        }
        else
            ++it;
    }
}

bool MeshRenderer::removeMesh(MeshComponent* mesh)
{
    bool result = false;
    std::list<MeshComponent*>::iterator it;

    for (it = this->meshes.begin(); it != this->meshes.end(); ++it)
    {
        if (*it == mesh)
        {
            break;
        }
    }

	if (it != this->meshes.end())
	{
		this->meshes.erase(it);
		result = true;
	}

    return result;
}

} // namespace
