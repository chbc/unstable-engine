#pragma once

#include "Mesh.h"

namespace sre
{

class MeshLoader
{
public:
	virtual Mesh* load(const char* fileName);
	void release(Mesh* mesh);

protected:
	template <typename TMesh, typename TVertex>
	Mesh* internalLoad(const char* fileName);
};

class GIUMeshLoader : public MeshLoader
{
public:
	Mesh* load(const char* fileName) override;
};

} // namespace
