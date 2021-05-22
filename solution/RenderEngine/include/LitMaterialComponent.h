#ifndef _LIT_MATERIAL_COMPONENT_H_
#define _LIT_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"

namespace sre
{

class LitMaterialComponent : public AMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
    float shininess;

public:
    LitMaterialComponent(Material* material);
    
    void setShininess(float shininess);
    float getShininess();
};

} // namespace

#endif
