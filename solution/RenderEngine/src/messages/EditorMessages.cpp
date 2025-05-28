#include "EditorMessages.h"
#include "AEditorPopup.h"

namespace sre
{

IMPLEMENT_MESSAGE(EntitySelectionMessage)
IMPLEMENT_MESSAGE(ExitEditorMessage)
IMPLEMENT_MESSAGE(FileDropEditorMessage)
IMPLEMENT_MESSAGE(ShowPopupEditorMessage)

ShowPopupEditorMessage::ShowPopupEditorMessage(AEditorPopup* arg_popup) : popup(arg_popup)
{ }

} // namespace
