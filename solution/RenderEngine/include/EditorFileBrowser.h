#if defined(DEBUG) && !defined(__ANDROID__)
#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorFileBrowser : public IEditorWindow
{

private:
	class TextureManager* textureManager = nullptr;
	void* textureId = nullptr;

public:
	void onInit() override;
	void onEditorGUI() override;
};

} // namespace

#endif
