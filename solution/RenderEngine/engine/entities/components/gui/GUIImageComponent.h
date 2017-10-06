#ifndef _GUI_IMAGE_COMPONENT_H_
#define _GUI_IMAGE_COMPONENT_H_

#include "../AEntityComponent.h"
#include <engine/utils/memory_aliases.h>
#include <engine/core/graphics/meshData/MeshData.h>

namespace sre
{

class GUIImageComponent : public AEntityComponent
{
private:
	uint32_t textureId;

	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;

	glm::vec2 uiPosition;
	bool isDynamic;

protected:
	VECTOR_UPTR<MeshData<GUIVertexData>> meshData;

protected:
	GUIImageComponent(Entity *entity, bool isDynamic = false);

public:
	void setUIPosition(const glm::vec2 &position);
	glm::vec2 getUIPosition();
	virtual uint32_t getTextureId();
	inline bool getIsDynamic() { return this->isDynamic; }

private:
	void load(const std::string &fileName);
	void loadFromAtlas(const std::string &fileName, const std::string &imageId);

friend class Entity;
friend class OpenGLAPI;
friend class GUIRenderer;
friend class GUIManager;
};

} // namespace

#endif
