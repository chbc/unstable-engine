#ifndef _GUI_RENDERER_H_
#define _GUI_RENDERER_H_

#include <engine/utils/memory_aliases.h>
#include <list>

namespace sre
{

class GUIImageComponent;
class AGraphicsWrapper;
class ShaderManager;
class MatrixManager;

class GUIRenderer
{
private:
	std::list<GUIImageComponent *> guiComponents;

	uint32_t shaderProgram;

	SPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

private:
	GUIRenderer(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader();
	void addGUIComponent(GUIImageComponent *guiComponent);
	void removeGUIComponent(GUIImageComponent *guiComponent);
	void render();

friend class RenderManager;
};

} // namespace

#endif
