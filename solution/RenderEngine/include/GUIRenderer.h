#pragma once

#include <list>
#include "memory_aliases.h"

namespace sre
{

class ABaseGUIComponent;
class GUIImageComponent;
class GUITextComponent;
class AGraphicsWrapper;
class ShaderManager;

class GUIRenderer
{
protected:
    std::list<GUIImageComponent*> imageComponents;
    std::list<GUITextComponent*> textComponents;
    uint32_t program{ 0 };

    ShaderManager* shaderManager{ nullptr };
    AGraphicsWrapper* graphicsWrapper{ nullptr };

public:
    ~GUIRenderer();

private:
    GUIRenderer(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void loadShader();
    void addImageComponent(GUIImageComponent* imageComponent);
    void addTextComponent(GUITextComponent* textComponent);
    void render();
    void setup(ABaseGUIComponent* guiComponent);

    void removeDestroyedEntities();

    bool isEmpty();

friend class RenderManager;
};

} // namespace
