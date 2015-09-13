#include "DiffuseMaterial.h"
#include <iostream>
#include <engine/systems/graphics/RenderManager.h>

using namespace graphics;

DiffuseMaterial::DiffuseMaterial(const std::string &fileName) : Material()
{
	this->loadShader(shaderConsts::DIFFUSE_V, shaderConsts::DIFFUSE_F);
	this->loadTexture(fileName);
}

DiffuseMaterial::~DiffuseMaterial()
{
    Texture *texture = NULL;
    for (unsigned int i = 0; i < this->textures.size(); i++)
    {
        texture = this->textures[i];
        if (texture != NULL)
        {
            // TODO: renderManager->removeTexture(texture->id);
            delete texture;
        }
    }

    this->textures.clear();
}

void DiffuseMaterial::loadTexture(const std::string &fileName)
{
    Texture *texture = this->renderManager->loadTexture(fileName);
    this->textures.push_back(texture);
}

void DiffuseMaterial::apply(std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->renderManager->applyMaterial(this, vertexData, receiveLight);
}

unsigned int DiffuseMaterial::getTextureID(int index)
{
    if (index >= this->textures.size())
        throw "[DiffuseMaterial] texture index out of range!";

    return this->textures[index]->id;
}
