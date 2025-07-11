#pragma once

#include "AEditorProperty.h"
#include "memory_aliases.h"

#include <string>

namespace sre
{

enum class EMaterialType
{
	STANDARD,
	CUSTOM
};

class ABaseMaterial
{
protected:
	std::string filePath{ "DefaultMaterial" };
	EMaterialType type;
	std::vector<SPTR<AEditorProperty>> editorProperties;

protected:
	ABaseMaterial(const std::string& arg_filePath, EMaterialType arg_type);

public:
	bool isStandard();
	const std::string& getFilePath() const;

protected:
	virtual void onPropertySerialized() {}
	virtual void onPropertyDeserialized() {}
	virtual void onPropertyChanged() {}
	void addEditorProperty(AEditorProperty* editorProperty);

friend class MaterialLoader;
friend class AssetsManager;
friend class MaterialEditorProperty;
};

} // namespace
