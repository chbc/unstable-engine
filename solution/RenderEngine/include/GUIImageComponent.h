#pragma once

#include "ABaseGUIComponent.h"

namespace sre
{

class SRE_API GUIImageComponent : public ABaseGUIComponent
{
DECLARE_COMPONENT()

private:
    class Texture* texture{ nullptr };
    class TextureEditorProperty* textureEditorProperty{ nullptr };

public:
    GUIImageComponent(Entity *entity);
    ~GUIImageComponent();

    uint32_t getTextureId() override;

protected:
    bool isAbleToBeRendered();

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
