#ifndef _LIT_MATERIAL_COMPONENT_H_
#define _LIT_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"

namespace sre
{

class LitMaterialComponent : public AMaterialComponent
{
private:
    float shininess;

public:
    LitMaterialComponent(Material *material)
        : AMaterialComponent(material), shininess(50)
    { }
    
    inline void setShininess(float shininess) { this->shininess = shininess; }
    inline float getShininess() { return this->shininess; }
};

} // namespace

#endif
