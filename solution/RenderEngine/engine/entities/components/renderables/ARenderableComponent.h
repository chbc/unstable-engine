#ifndef _A_RENDERABLE_COMPONENT_H_
#define _A_RENDERABLE_COMPONENT_H_

#include "../AEntityComponent.h"
#include <engine/utils/memory_aliases.h>
#include <engine/core/graphics/meshData/MeshData.h>

namespace sre
{

class Entity;

template <typename TVertexData>
class ARenderableComponent : public AEntityComponent
{
protected:
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
    UPTR<MeshData<TVertexData>> meshData;

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
