#pragma once

#include <unordered_map>
#include <string>

#include "ASingleton.h"
#include "Mesh.h"

namespace sre
{

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	std::unordered_map<size_t, UPTR<Mesh>> meshesMap;

public:
	Mesh* loadMesh(const char* file);

private:
	size_t generateKey(const char* input);

	void release() override;
};

} // namespace
