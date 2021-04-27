#pragma once

namespace sre
{

class IEditorWindow
{
public:
	virtual void onInit() {}
	virtual void onEditorGUI() = 0;
	virtual void onRelease() {}
};

} // namespace
