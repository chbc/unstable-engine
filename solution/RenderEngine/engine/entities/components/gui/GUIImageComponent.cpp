#include "GUIImageComponent.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/systems/multimedia/textures/Texture.h>
#include <engine/entities/components/transforms/TransformComponent.h>

namespace sre
{

GUIImageComponent::GUIImageComponent(Entity *entity, const std::string &fileName)
	: AEntityComponent(entity)
{
	float half = 0.5f;

	float planeVertices[] = 
	{ 
		-half, half,
		-half,-half,
		half,-half,
		half, half
	};

	unsigned char planeIndices[] = 
	{ 
		0, 1, 2,
		2, 3, 0 
	};

	float planeTexCoords[] = 
	{ 
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};
	
	VECTOR_UPTR<GUIVertexData> vertexData;
	GUIVertexData *newData;
	// Positions
	for (int i = 0; i < 8; i += 2)
	{
		newData = new GUIVertexData;
		newData->position = glm::vec2(planeVertices[i], planeVertices[i + 1]);

		vertexData.emplace_back(newData);
	}

	// UVs
	for (int i = 0; i < 4; i++)
	{
		vertexData[i]->u = planeTexCoords[2 * i];
		vertexData[i]->v = planeTexCoords[(2 * i) + 1];
	}
	
	// Indices
	this->indices;
	for (int i = 0; i < 6; i++)
		indices.push_back(planeIndices[i]);

	this->vertexData = std::move(vertexData);
	this->texture = RenderManager::getInstance()->loadDiffuseTexture(fileName);
}

GUIImageComponent::~GUIImageComponent()
{
	this->vertexData.clear();
	this->indices.clear();
}

void GUIImageComponent::setPosition(const glm::vec2 &position)
{
	this->getTransform()->setPosition(glm::vec3(position, 0.0f));
}

glm::vec2 GUIImageComponent::getPosition()
{
	glm::vec3 position3 = this->getTransform()->getPosition();
	return glm::vec2(position3.x, position3.y);
}

} // namespace
