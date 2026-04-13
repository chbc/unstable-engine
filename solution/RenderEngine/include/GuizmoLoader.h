#pragma once

#include "ColorMeshData.h"
#include "EGuizmoMesh.h"

namespace sre
{

class AGraphicsWrapper;

class GuizmoLoader
{
private:
    ColorMeshData* load(EGuizmoType type);
    void release(ColorMeshData* mesh);

friend class AssetsManager;
};

} // namespace
