#pragma once

#include "AMaterialComponent.h"

namespace sre
{

class LitMaterialComponent : public AMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
    float shininess;

public:
    LitMaterialComponent(ABaseMaterial* material);
    
    void setShininess(float shininess);
    float getShininess();
};

} // namespace
