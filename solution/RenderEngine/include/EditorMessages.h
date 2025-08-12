#pragma once

#include "BaseMessage.h"
#include "core_defines.h"

#include <string>

namespace sre
{

class AEditorPopup;
class Entity;

struct SRE_API EntitySelectionMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	Entity* entity;

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
	ShowPopupEditorMessage(AEditorPopup* arg_popup) : popup(arg_popup) {}
};

struct EntityChangedEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()
};

struct SRE_API MeshImportedEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	std::string filePath;
	float scaleFactor;
	MeshImportedEditorMessage(const std::string& arg_filePath, float arg_scaleFactor)
		: filePath(arg_filePath), scaleFactor(arg_scaleFactor) {}
};

struct SRE_API MeshEntityLoadedEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	Entity* entity;
	MeshEntityLoadedEditorMessage(Entity* arg_entity) : entity(arg_entity) {}
};

struct ChangeGuizmoModeMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	int mode{ 0 };
	ChangeGuizmoModeMessage(int arg_mode) : mode(arg_mode) { }
};

} // namespace
