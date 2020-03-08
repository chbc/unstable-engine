#include "Renderer.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "AGraphicsWrapper.h"
#include "MatrixManager.h"
#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "LightManager.h"

#include "LightRendererShaderSetup.h"


// ### ANDROID
#include <SDL_log.h>

namespace sre
{

Renderer::Renderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
    LightManager * lightManager = SingletonsManager::getInstance()->get<LightManager>();

    // ### COLOCAR NUM FACTORY
    for (std::size_t i = EComponentId::COLOR_MATERIAL; i <= EComponentId::AO_MATERIAL; i++)
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
                default: break;
            }
        }
    }
}

Renderer::~Renderer()
{
    for (MeshComponent *item : this->meshes)
        this->graphicsWrapper->deleteBuffers(item);
}

void Renderer::onSceneLoaded()
{
	SDL_Log("XXX Renderer - onSceneLoaded 1");
    this->loadShaderSetupItems();
	SDL_Log("XXX Renderer - onSceneLoaded 2");
    this->loadShader();
	SDL_Log("XXX Renderer - onSceneLoaded 3");

    for (const auto &item : this->shaderSetupItems)
        item.second->onSceneLoaded(this->shader);

	SDL_Log("XXX Renderer - onSceneLoaded 4");

    for (const auto &item : this->componentsMap)
        item.second->onSceneLoaded(this->shader);
	SDL_Log("XXX Renderer - onSceneLoaded 5");
}

void Renderer::loadShaderSetupItems()
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

void Renderer::loadShader()
{
    this->shader = this->shaderManager->loadShader(this->componentsBitset, this->lightData);
}

void Renderer::addMesh(MeshComponent *mesh)
{
    this->meshes.push_back(mesh);
    this->graphicsWrapper->createVAO(mesh);
    this->graphicsWrapper->createEBO(mesh);
}

void Renderer::render(MatrixManager *matrixManager, const glm::vec3 &cameraPosition)
{
    // Shader setup
    this->shaderManager->enableShader(this->shader);

    for (const auto &item : this->shaderSetupItems)
        item.second->setupShaderValues(this->shader, cameraPosition);

    for (MeshComponent *mesh : this->meshes)
    {
        // Matrix setup
        TransformComponent *transform = mesh->getTransform();
        glm::mat4 modelMatrix = transform->getMatrix();
        this->shaderManager->setMat4(this->shader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

        this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
        for (const auto &item : this->componentsMap)
        {
            item.second->setupShaderValues(mesh, this->shader);
            item.second->preDraw();
        }

        this->graphicsWrapper->drawElement(mesh->meshData->indices.size());
    }

    for (const auto &item : this->componentsMap)
        item.second->postDraw();

    this->shaderManager->disableShader();
}

bool Renderer::contains(MeshComponent *mesh)
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

bool Renderer::fitsWithMesh(MeshComponent *mesh)
{
    return (this->componentsBitset == mesh->getMaterial()->componentsBitset);
}

void Renderer::removeDestroyedEntities()
{
    std::list<MeshComponent *>::iterator it;

    for (it = this->meshes.begin(); it != this->meshes.end(); )
    {
        if (!(*it)->getEntity()->isAlive())
        {
            this->graphicsWrapper->deleteBuffers((*it));
            it = this->meshes.erase(it);
        }
        else
            ++it;
    }
}

} // namespace