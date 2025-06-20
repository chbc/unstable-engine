#pragma once

#include "ARenderableComponent.h"
#include "MeshData.h"

namespace sre
{

class SRE_API ABaseGUIComponent : public ARenderableComponent
{
protected:
    MeshData2D* meshData{ nullptr };

public:
    ABaseGUIComponent(Entity* entity);
    virtual ~ABaseGUIComponent() = default;

    virtual uint32_t getTextureId() = 0;

protected:
    void onPropertyDeserialized() override;
    void loadMesh();

friend class GUIRenderer;
};

} // namespace
