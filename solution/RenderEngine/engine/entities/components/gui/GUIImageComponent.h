#ifndef _GUI_IMAGE_COMPONENT_H_
#define _GUI_IMAGE_COMPONENT_H_

#include "../AEntityComponent.h"
#include <engine/utils/memory_aliases.h>
#include <engine/entities/components/meshes/VertexData.h>

namespace sre
{

class Texture;

class GUIImageComponent : public AEntityComponent
{
private:
	Texture *texture;

	VECTOR_UPTR<GUIVertexData> vertexData;
	std::vector<uint32_t> indices;

	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;

private:
	GUIImageComponent(Entity *entity, const std::string &fileName);

public:
	~GUIImageComponent();

	void setPosition(const glm::vec2 &position);
	glm::vec2 getPosition();

friend class Entity;
friend class OpenGLAPI;
friend class GUIRenderer;
};

} // namespace

#endif
