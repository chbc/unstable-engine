#include "LightManager.h"

#include <engine/nodes/lights/DirectionalLight.h>
#include <engine/nodes/lights/PointLight.h>
#include "ShaderManager.h"
#include <stdio.h>

namespace sre
{

IMPLEMENT_SINGLETON(LightManager);

LightManager::LightManager()
{
}

bool LightManager::init()
{
	return true;
}

void LightManager::release()
{
	std::vector<LightNode *>::iterator itLight = this->lightNodes.begin();
	while(itLight != this->lightNodes.end())
	{
		delete (*itLight);
		itLight++;
	}
	this->lightNodes.clear();
}

DirectionalLight *LightManager::addDirectionalLight()
{
	DirectionalLight *newLight = new DirectionalLight();
	this->lightNodes.push_back(newLight);

	return newLight;
}

PointLight *LightManager::addPointLight()
{
	PointLight *newLight = new PointLight();
	this->lightNodes.push_back(newLight);

	return newLight;
}

void LightManager::setupLights(unsigned int program)
{
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
}

} // namespace
