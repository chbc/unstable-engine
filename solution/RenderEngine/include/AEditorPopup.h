#pragma once

#include "imgui/imgui.h"

#include <functional>

namespace sre
{

class EditorsController;
class AEditorPopup;

using Action_OnClosePopup = std::function<void(AEditorPopup*, bool)>;

class AEditorPopup
{
private:
	bool open{ true };
	Action_OnClosePopup* onCloseAction{ nullptr };

public:
	AEditorPopup(Action_OnClosePopup* arg_onCloseAction);
	virtual ~AEditorPopup() = default;

	virtual void onEditorGUI() = 0;
	void close(bool confirmed);
	inline bool isOpen() const { return this->open; }
};

} // namespace
