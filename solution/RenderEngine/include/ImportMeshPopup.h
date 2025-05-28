#pragma once

#include "AEditorPopup.h"

#include <string>

namespace sre
{

class ImportMeshPopup : public AEditorPopup
{
public:
	std::string sourceFilePath;
	std::string destinationPath;
	static float scaleFactor;
	static bool loadToScene;

public:
	ImportMeshPopup(Action_OnClosePopup* onCloseAction, std::string arg_sourceFilePath, std::string arg_destinationPath);

	void onEditorGUI() override;
};

} // namespace
