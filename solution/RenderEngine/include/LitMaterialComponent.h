#pragma once

#include "AMaterialComponent.h"

namespace sre
{

class LitMaterialComponent : public AMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

public:
    LitMaterialComponent(ABaseMaterial* material);
};

} // namespace
