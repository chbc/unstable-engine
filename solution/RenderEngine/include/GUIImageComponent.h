#pragma once

#include "AEntityComponent.h"
#include "Model.h"

namespace sre
{

class SRE_API GUIImageComponent : public AEntityComponent
{
DECLARE_COMPONENT()

protected:
    MeshData2D* meshData{ nullptr };
    uint32_t maxItems{ 0 }; // ###
	class TextureEditorProperty* textureEditorProperty{ nullptr };

private:
    class Texture* texture{ nullptr };
    bool isDynamic{ false }; // ###

public:
    GUIImageComponent(Entity *entity);
    virtual ~GUIImageComponent();
    void setMaxItems(uint32_t arg_maxItems);
    virtual uint32_t getTextureId();
    inline bool getIsDynamic() { return this->isDynamic; }

protected:
    bool isAbleToBeRendered();
    virtual void onPropertyDeserialized() override;

private:
    void load(const std::string& filePath);
    void load(const std::string &filePath, const glm::vec2& normalizedSize);
    void loadFromAtlas(const std::string &filePath, const std::string &imageId);

friend class Entity;
friend class OpenGLAPI;
friend class OpenGLESAPI;
friend class GUIRenderer;
friend class GUIScene;
friend class RenderManager;
};

} // namespace
