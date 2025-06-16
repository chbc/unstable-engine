#pragma once

#include <list>
#include "memory_aliases.h"

namespace sre
{

class GUIImageComponent;
class AGraphicsWrapper;
class ShaderManager;

class GUIRenderer
{
protected:
    std::list<GUIImageComponent *> guiComponents;
    std::list<GUIImageComponent *> dynamicGuiComponents;
    uint32_t shaderProgram;

    ShaderManager* shaderManager{ nullptr };
    AGraphicsWrapper* graphicsWrapper{ nullptr };

private:
    class Shader *shader;

public:
    ~GUIRenderer();

private:
    GUIRenderer(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void loadShader();
    void addGUIComponent(GUIImageComponent *guiComponent);
    void addDynamicGUIComponent(GUIImageComponent *guiComponent);
    void render();
    void setup(GUIImageComponent *guiComponent);

    void removeDestroyedEntities();

    bool isEmpty();

friend class RenderManager;
};

} // namespace
