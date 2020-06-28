#ifndef _A_RENDERABLE_COMPONENT_H_
#define _A_RENDERABLE_COMPONENT_H_

#include "AEntityComponent.h"
#include "memory_aliases.h"
#include "MeshData.h"

namespace sre
{

class Entity;

class SRE_API ARenderableComponent : public AEntityComponent
{
protected:
    UPTR<AMeshData> meshData;

protected:
    ARenderableComponent(Entity *entity) : AEntityComponent(entity) { }

    bool isAbleToBeRendered()
    {
        return
        (
            (this->meshData.get() != nullptr) &&
            !this->meshData->indices.empty()
        );
    }
};

} // namespace

#endif
