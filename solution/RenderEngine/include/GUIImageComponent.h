#pragma once

#include "AEntityComponent.h"
#include "MeshData.h"

namespace sre
{

class SRE_API GUIImageComponent : public AEntityComponent
{
DECLARE_COMPONENT()

protected:
    GUIMeshData* meshData{ nullptr };
    uint32_t maxItems{ 0 }; // ###

private:
    glm::vec2 uiPosition;
    glm::vec2 extent;
    glm::vec2 pivot;
    class Texture* texture{ nullptr };
    bool isDynamic{ false }; // ###

public:
    GUIImageComponent(Entity *entity);
    virtual ~GUIImageComponent();
    void setMaxItems(uint32_t arg_maxItems);
	void setUIPosition(const glm::vec2 &position);
    glm::vec2 getUIPosition();
    virtual uint32_t getTextureId();
    glm::vec2 getExtent();
    void setPivot(const glm::vec2& pivot);
    inline bool getIsDynamic() { return this->isDynamic; }

protected:
    bool isAbleToBeRendered();
	virtual void onPropertyChanged() override;

private:
    void load(const std::string& fileName);
    void load(const std::string &fileName, const glm::vec2& normalizedSize);
    void loadFromAtlas(const std::string &fileName, const std::string &imageId);
    void updateTransform();

friend class Entity;
friend class OpenGLAPI;
friend class OpenGLESAPI;
friend class GUIRenderer;
friend class GUIScene;
friend class RenderManager;
};

} // namespace
