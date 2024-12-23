#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorFileBrowser.h"
#include "SingletonsManager.h"
#include "TextureManager.h"

#include "imgui/imgui.h"

namespace sre
{

void EditorFileBrowser::onInit()
{
	if (this->textureManager == nullptr)
	{
		this->textureManager = SingletonsManager::getInstance()->get<TextureManager>();
		Texture* texture = this->textureManager->loadGUITexture("crate.png");
		this->textureId = reinterpret_cast<void*>(texture->getId());
	}
}

void EditorFileBrowser::onEditorGUI()
{
	ImGui::Begin("File Browser");
	const ImVec2 size{ 32, 32 };
	ImGui::Image(this->textureId, size);
	ImGui::End();
}

} // namespace

#endif
