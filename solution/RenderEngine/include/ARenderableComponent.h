#ifndef _A_RENDERABLE_COMPONENT_H_
#define _A_RENDERABLE_COMPONENT_H_

#include "AEntityComponent.h"
#include "memory_aliases.h"
#include "Mesh.h"

namespace sre
{

class Entity;

class SRE_API ARenderableComponent : public AEntityComponent
{
protected:
    UPTR<Mesh> mesh;

private:
    bool opaque;

protected:
    ARenderableComponent(Entity* entity);

public:
    inline void setIsOpaque(bool value) { this->opaque = value; }

protected:
    inline bool isAbleToBeRendered()
    {
        return
        (
            (this->mesh->meshData.get() != nullptr) &&
            !this->mesh->meshData->indices.empty()
        );
    }

    inline bool isOpaque() { return this->opaque; }
};

} // namespace

#endif
