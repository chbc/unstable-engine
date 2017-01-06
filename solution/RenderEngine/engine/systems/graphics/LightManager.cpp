#include "LightManager.h"

#include <engine/entities/Entity.h>
#include "ShaderManager.h"

namespace sre
{

LightManager::LightManager()
{
	this->ambientLightColor = glm::vec3(0.3f, 0.3f, 0.3f);
}

LightManager::~LightManager()
{
	/* ####
	std::vector<LightNode *>::iterator itLight = this->lightNodes.begin();
	while(itLight != this->lightNodes.end())
	{
		delete (*itLight);
		itLight++;
	}
	this->lightNodes.clear();
	*/
}

DirectionalLightComponent *LightManager::addDirectionalLight(Entity *entity)
{
	DirectionalLightComponent *newLight = entity->addComponent<DirectionalLightComponent>();
	this->directionalLights.push_back(newLight);

	return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
	PointLightComponent *newLight = entity->addComponent<PointLightComponent>();
	this->pointLights.push_back(newLight);

	return newLight;
}

void LightManager::setupLights(ShaderManager *shaderManager, uint32_t program)
{
	this->setupDirectionalLights(shaderManager, program);
	this->setupPointLights(shaderManager, program);

	shaderManager->setValue(program, "ambientLightColor", 1, &this->ambientLightColor[0]);
}

void LightManager::setupDirectionalLights(ShaderManager *shaderManager, uint32_t program)
{
    char variable[100];

    DirectionalLightComponent *light = nullptr;
    int count = this->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->directionalLights[i];
		glm::vec3 direction = light->getDirection();
		glm::vec3 color = light->getColor();

        sprintf_s(variable, "directionalLights[%d].direction", i);
        shaderManager->setValue(program, variable, direction.x, direction.y, direction.z);

        sprintf_s(variable, "directionalLights[%d].color", i);
        shaderManager->setValue(program, variable, color.r, color.g, color.b);
    }

    shaderManager->setValue(program, "directionalLightsCount", count);
}

void LightManager::setupPointLights(ShaderManager *shaderManager, uint32_t program)
{
	/*
    char variable[100];

    ALightComponent *light = nullptr;
    int size = this->lights.size();
    for (int i = 0; i < size; i++)
    {
        light = this->lightNodes[i];

        sprintf(variable, "lights[%d].posDir", i);
        shaderManager->setValue(program, variable, light->posDir.x, light->posDir.y, light->posDir.z);

        sprintf(variable, "lights[%d].color", i);
        shaderManager->setValue(program, variable, 1, light->color.y, light->color.z);

        sprintf(variable, "lights[%d].type", i);
        shaderManager->setValue(program, variable, light->getType());
    }

    shaderManager->setValue(program, "lightCount", size);
	*/
}

} // namespace
