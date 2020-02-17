#include "MeshData.h"

namespace sre
{

// ABaseVertexData
void *ABaseVertexData::getUVOffset()
{
	return (void *)0;
}

// GUIVertexData
void *GUIVertexData::getPositionOffset()
{
	return (void *)(sizeof(float) * 2);
}

// VertexData
void *VertexData::getPositionOffset()
{
	return (void *)(sizeof(float) * 2);
}

void *VertexData::getNormalOffset()
{
	return (void *)(sizeof(glm::vec3) + (sizeof(float) * 2));
}

void *VertexData::getTangentOffset()
{
	return (void *)((sizeof(glm::vec3) * 2) + (sizeof(float) * 2));
}

void *VertexData::getBitangentOffset()
{
	return (void *)((sizeof(glm::vec3) * 3) + (sizeof(float) * 2));
}

} // namespace
