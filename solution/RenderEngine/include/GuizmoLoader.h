#pragma once

#include "ColorMeshData.h"

namespace sre
{

class AGraphicsWrapper;

class GuizmoLoader
{
private:
    ColorMeshData* load(const std::string &type);
    void release(ColorMeshData* mesh);

friend class AssetsManager;
};

} // namespace
