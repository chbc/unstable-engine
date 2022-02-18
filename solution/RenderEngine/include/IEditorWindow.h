#pragma once

#include <stdint.h>

namespace sre
{

class IEditorWindow
{
public:
	virtual void onInit() {}
	virtual void onUpdate(uint32_t elapsedTime) {}
	virtual void onEditorGUI() = 0;
	virtual void onRelease() {}
};

} // namespace
