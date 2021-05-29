#pragma once

#include "IEditorWindow.h"
#include "Texture.h"

namespace sre
{

class EditorSceneViewport : public IEditorWindow
{
private:
	class RenderManager* renderManager;

	static uint32_t Fbo;
	void* textureId;

public:
	EditorSceneViewport();

	void onInit() override;
	void onEditorGUI() override;
	void onRelease() override;

friend class WorldEditor;
};

} // namespace
