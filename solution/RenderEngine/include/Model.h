#pragma once

#include "MeshData.h"
#include "memory_aliases.h"
#include "core_defines.h"

#include <string>
#include <unordered_map>

namespace sre
{

struct ABaseModel
{
private:
	std::string filePath;

public:
	ABaseModel(const char* arg_filePath);
	const std::string& getFilePath();
	virtual bool isEmpty() = 0;

friend class AssetsManager;
};

struct Model : ABaseModel
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

struct Model2D : ABaseModel
{
public:
	std::unordered_map<std::string, UPTR<MeshData2D>> meshes;

public:
	Model2D(const char* arg_filePath);
	MeshData2D* getMesh(const char* meshName);
	bool isEmpty() override;
};

} // namespace
