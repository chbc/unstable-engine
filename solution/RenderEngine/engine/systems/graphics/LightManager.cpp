#include "LightManager.h"

#include <engine/entities/Entity.h>
// #include "ShaderManager.h"

namespace sre
{

LightManager::~LightManager()
{
	/*
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
	// ### this->lightComponents.push_back(UPTR<DirectionalLightComponent>(newLight));

	return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
	PointLightComponent *newLight = entity->addComponent<PointLightComponent>();
	// ### this->lightComponents.push_back(UPTR<PointLightComponent>(newLight));

	return newLight;
}

void LightManager::setupLights(unsigned int program)
{
	/*
    ShaderManager *shaderManager = ShaderManager::getInstance();

    char variable[100];
    LightNode *light = NULL;
    int size = this->lightNodes.size();
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
