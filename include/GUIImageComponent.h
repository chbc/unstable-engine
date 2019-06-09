#ifndef _GUI_IMAGE_COMPONENT_H_
#define _GUI_IMAGE_COMPONENT_H_

#include "ARenderableComponent.h"

namespace sre
{

class GUIImageComponent : public ARenderableComponent<GUIVertexData>
{
private:
    glm::vec2 uiPosition;
    uint32_t textureId;

protected:
    uint32_t maxItems; // ###

private:
    bool isDynamic; // ###

protected:
    GUIImageComponent(Entity *entity, uint32_t arg_maxItems = 0);

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
friend class RenderManager;
};

} // namespace

#endif
