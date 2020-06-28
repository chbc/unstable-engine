#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "AComponentsHolder.h"
#include "AMaterialComponent.h"
#include "memory_aliases.h"
#include "ColorMaterialComponent.h"
#include "LitMaterialComponent.h"
#include "DiffuseMaterialComponent.h"
#include "NormalMaterialComponent.h"
#include "SpecularMaterialComponent.h"
#include "AmbientOcclusionMaterialComponent.h"
#include "OutlineMaterialComponent.h"

/* ###
- passar flags pelo construtor
- adicionar components baseado nas flags
*/

namespace sre
{

class Material : public AComponentsHolder<AMaterialComponent>
{
private:
    bool castsShadow;

public:
	SRE_API inline void setCastsShadow(bool value);
	SRE_API void setReceivesLight(bool value);
	SRE_API bool getReceivesLight();

private:
    Material();

    template <typename T, typename... TArgs>
    T *addComponent(TArgs&&... mArgs)
    {
        T *newComponent{ nullptr };

        if (!AComponentsHolder<AMaterialComponent>::hasComponent<T>())
        {
            newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
            AComponentsHolder<AMaterialComponent>::addComponent(newComponent);
        }
        else
            throw "Can't add duplicate component!";

        return newComponent;
    }

friend class MeshComponent;
friend class MeshRenderer;
friend class RenderManager;
};

} // namespace

#endif
