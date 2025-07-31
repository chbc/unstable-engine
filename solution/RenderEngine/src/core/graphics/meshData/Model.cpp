#include "Model.h"
#include "FileUtils.h"

namespace sre
{

ABaseModel::ABaseModel(const char* arg_filePath)
{
	this->filePath = FileUtils::getContentRelativePath(arg_filePath);
}

const std::string& ABaseModel::getFilePath()
{
	return this->filePath;
}

Model::Model(const char* arg_filePath) : ABaseModel(arg_filePath)
{
}

MeshData* Model::getMesh(const char* meshName)
{
	MeshData* result = nullptr;

	if (!this->meshes.empty())
	{
		if (this->meshes.count(meshName) > 0)
		{
			result = this->meshes[meshName].get();
		}
		else
		{
			result = this->meshes.begin()->second.get();
		}
	}

	return result;
}

size_t Model::getMeshCount()
{
	return this->meshes.size();
}

bool Model::isEmpty()
{
	return this->meshes.empty();
}

Model2D::Model2D(const char* arg_filePath) : ABaseModel(arg_filePath)
{
}

MeshData2D* Model2D::getMesh(const char* meshName)
{
	MeshData2D* result = nullptr;

	if (this->meshes.count(meshName) > 0)
	{
		result = this->meshes[meshName].get();
	}

	return result;
}

bool Model2D::isEmpty()
{
	return this->meshes.empty();
}

} // namespace
