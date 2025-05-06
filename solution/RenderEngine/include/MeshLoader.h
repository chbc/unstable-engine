#pragma once

#include "Model.h"

namespace sre
{

class ABaseMeshLoader
{
protected:
	template <typename TModel, typename TMesh, typename TVertex>
	TModel* internalLoad(const char* filePath);

	template <typename TModel, typename TMesh>
	void internalRelease(TModel* model);

private:
	template <typename TMesh, typename TVertex>
	TMesh* loadMesh(std::ifstream& readStream);
};

class MeshLoader : public ABaseMeshLoader
{
public:
	Model* load(const char* filePath);
	void release(Model* model);
};

class GUIMeshLoader : public ABaseMeshLoader
{
public:
	Model2D* load(const char* filePath);
	void release(Model2D* model);
};

} // namespace
