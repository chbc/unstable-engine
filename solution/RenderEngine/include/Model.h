#pragma once

#include "AAsset.h"
#include "MeshData.h"
#include "memory_aliases.h"
#include "core_defines.h"

#include <unordered_map>

namespace sre
{

class ABaseModel : public AAsset
{
public:
	ABaseModel(const char* arg_filePath);
	virtual ~ABaseModel() = default;
	virtual bool isEmpty() = 0;
};

class Model : public ABaseModel
{
public:
	// mesh name, mesh data
	std::unordered_map<std::string, UPTR<MeshData>> meshes;

public:
	SRE_API Model(const char* arg_filePath);
	MeshData* getMesh(const char* meshName);
	SRE_API size_t getMeshCount();
	bool isEmpty() override;
};

class Model2D : public ABaseModel
{
public:
	std::unordered_map<std::string, UPTR<MeshData2D>> meshes;

public:
	Model2D(const char* arg_filePath);
	MeshData2D* getMesh(const char* meshName);
	bool isEmpty() override;
};

} // namespace
