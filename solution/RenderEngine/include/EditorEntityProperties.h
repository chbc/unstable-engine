#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "AEntityComponent.h"
#include <glm/vec3.hpp>
#include <vector>
#include <unordered_map>

namespace sre
{

class EditorEntityProperties : public IEditorWindow
{
private:
	class Entity* entity;

public:
	EditorEntityProperties();
	void onEditorGUI() override;
	void onRelease() override;

private:
	void onEntitySelected(void* data);
};

} // namespace

#endif
