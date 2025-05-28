#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "BaseMessage.h"

#include <string>

namespace sre
{

class AEditorPopup;

struct EntitySelectionMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	class Entity* entity;

	EntitySelectionMessage(class Entity* arg_entity) : entity(arg_entity) {}
};

struct ExitEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()
};

struct FileDropEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	std::string filePath;
	FileDropEditorMessage(const std::string& arg_filePath) : filePath(arg_filePath) {}
};

struct ShowPopupEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	AEditorPopup* popup;
	ShowPopupEditorMessage(AEditorPopup* arg_popup);
};

} // namespace

#endif
