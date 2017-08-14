#include "GUIImageComponent.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/systems/multimedia/textures/Texture.h>
#include <engine/entities/components/transforms/TransformComponent.h>

namespace sre
{

GUIImageComponent::GUIImageComponent(Entity *entity, const std::string &fileName)
	: AEntityComponent(entity)
{
	this->texture = RenderManager::getInstance()->loadDiffuseTexture(fileName);

	float aspectRatio = MultimediaManager::getInstance()->getAspectRatio();
	float halfWidth = this->texture->getWidth() / MultimediaManager::getInstance()->getScreenWidth();
	float halfHeight = this->texture->getHeight() / MultimediaManager::getInstance()->getScreenHeight();

	halfWidth /= 2.0f;
	halfHeight /= 2.0f;


	float planeVertices[] = 
	{ 
		-halfWidth, halfHeight,
		-halfWidth,-halfHeight,
		halfWidth,-halfHeight,
		halfWidth, halfHeight
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
}

GUIImageComponent::~GUIImageComponent()
{
	this->vertexData.clear();
	this->indices.clear();
}

void GUIImageComponent::setUIPosition(const glm::vec2 &position)
{
	float aspectRatio = MultimediaManager::getInstance()->getAspectRatio();
	glm::vec3 realPosition = glm::vec3
	(
		((position.x * 2) - 1), 
		-(position.y * 2) + 1, 
		0.0f
	);
	this->getTransform()->setPosition(realPosition);

	this->uiPosition = position;
}

glm::vec2 GUIImageComponent::getUIPosition()
{
	return this->uiPosition;
}

} // namespace
