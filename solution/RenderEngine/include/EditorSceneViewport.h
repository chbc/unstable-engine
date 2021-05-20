#pragma once

#include "IEditorWindow.h"
#include "Texture.h"

namespace sre
{

class EditorSceneViewport : public IEditorWindow
{
private:
	class RenderManager* renderManager;

	uint32_t fbo;
	void* textureId;

public:
	EditorSceneViewport();

	void onInit() override;
	void onEditorGUI() override;
	void onRelease() override;
};

} // namespace
