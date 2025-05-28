#include "AEditorPopup.h"

namespace sre
{

AEditorPopup::AEditorPopup(Action_OnClosePopup* arg_onCloseAction) : onCloseAction(arg_onCloseAction)
{ }

void AEditorPopup::close(bool confirmed)
{
	this->open = false;

	ImGui::CloseCurrentPopup();

	if (this->onCloseAction)
	{
		(*this->onCloseAction)(this, confirmed);
	}
}

} // namespace
