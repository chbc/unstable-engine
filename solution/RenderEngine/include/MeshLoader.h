#pragma once

#include "Mesh.h"

namespace sre
{

class MeshLoader
{
public:
	virtual Mesh* load(const char* filePath);
	void release(Mesh* mesh);

protected:
	template <typename TMesh, typename TVertex>
	Mesh* internalLoad(const char* filePath);
};

class GIUMeshLoader : public MeshLoader
{
public:
	Mesh* load(const char* filePath) override;
};

} // namespace
