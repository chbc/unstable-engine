#pragma once

#include "AAsset.h"
#include "AEditorProperty.h"
#include "memory_aliases.h"
#include "EComponentId.h"

#include <bitset>
#include <unordered_map>

namespace sre
{

enum class EMaterialType
{
	STANDARD,
	CUSTOM
};

class AMaterialComponent;

class ABaseMaterial : public AAsset
{
private:
	std::unordered_map<size_t, SPTR<AMaterialComponent>> componentsMap;
	std::bitset<EComponentId::SIZE> componentsBitset;

protected:
	EMaterialType type;
	std::vector<SPTR<AEditorProperty>> editorProperties;

protected:
	ABaseMaterial(const std::string& arg_filePath, EMaterialType arg_type);

public:
	// XXX REMOVER?
	template <typename T> T* addComponent();
	template <typename T> void removeComponent();
	template <typename T> T* getComponent();
	template <typename T> bool hasComponent();

	AMaterialComponent* addComponent(const char* className);

	bool isStandard();

protected:
	virtual void onPropertySerialized() {}
	virtual void onPropertyDeserialized() {}
	virtual void onPropertyChanged() {}
	void addEditorProperty(AEditorProperty* editorProperty);

friend class MaterialLoader;
friend class AssetsManager;
friend class MaterialEditorProperty;
friend class MeshComponent;
friend class MeshRenderer;
};

struct MaterialHash
{
	size_t operator()(const ABaseMaterial* material) const
	{
		return std::hash<std::string>()(material->getFilePath());
	}
};

struct MaterialEqual
{
	bool operator()(const ABaseMaterial* material1, const ABaseMaterial* material2) const
	{
		return material1->getFilePath() == material2->getFilePath();
	}
};

} // namespace

#include "ABaseMaterial.tpp"
