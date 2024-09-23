#ifndef _GUI_IMAGE_COMPONENT_H_
#define _GUI_IMAGE_COMPONENT_H_

#include "ARenderableComponent.h"
#include <string>

namespace sre
{

class SRE_API GUIImageComponent : public ARenderableComponent
{
DECLARE_COMPONENT()

private:
    glm::vec2 uiPosition;
    glm::vec2 extent;
    glm::vec2 pivot;
    uint32_t textureId;
    bool isDynamic; // ###

protected:
    uint32_t maxItems; // ###

public:
    GUIImageComponent(Entity *entity);
    void setMaxItems(uint32_t arg_maxItems);
	void setUIPosition(const glm::vec2 &position);
    glm::vec2 getUIPosition();
    virtual uint32_t getTextureId();
    glm::vec2 getExtent();
    void setPivot(const glm::vec2& pivot);
    inline bool getIsDynamic() { return this->isDynamic; }

private:
    void load(const std::string& fileName);
    void load(const std::string &fileName, const glm::vec2& normalizedSize);
    void loadFromAtlas(const std::string &fileName, const std::string &imageId);

friend class Entity;
friend class OpenGLAPI;
friend class OpenGLESAPI;
friend class GUIRenderer;
friend class GUIScene;
friend class RenderManager;
};

} // namespace

#endif
