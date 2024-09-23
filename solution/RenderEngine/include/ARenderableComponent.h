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

private:
    bool opaque;

protected:
    ARenderableComponent(Entity* entity);

public:
    inline void setIsOpaque(bool value) { this->opaque = value; }
    void setMeshData(MeshData* meshData);

protected:
    inline bool isAbleToBeRendered()
    {
        return
        (
            (this->meshData.get() != nullptr) &&
            !this->meshData->indices.empty()
        );
    }

    inline bool isOpaque() { return this->opaque; }
};

} // namespace

#endif
