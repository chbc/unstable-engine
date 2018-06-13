#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <engine/entities/components/AComponentsHolder.h>
#include "components/AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>
#include "components/ColorMaterialComponent.h"
#include "components/DiffuseMaterialComponent.h"
#include "components/NormalMaterialComponent.h"
#include "components/SpecularMaterialComponent.h"
#include "components/AmbientOcclusionMaterialComponent.h"

/* ###
- passar flags pelo construtor
- adicionar components baseado nas flags
*/

namespace sre
{

class Material : public AComponentsHolder<AMaterialComponent>
{
private:
    float shininess;
    bool receivesLight;
    bool receivesShadow;
    bool castsShadow;

public:
    void setShininess(float shininess);
    float getShininess();

    inline void setCastsShadow(bool value) { this->castsShadow = value; }

private:
    Material(bool arg_receivesLight = true, bool arg_receivesShadow = true, bool arg_castsShadow = true, float arg_shininess = 15.0);

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
friend class Renderer;
friend class RenderManager;
};

} // namespace

#endif
