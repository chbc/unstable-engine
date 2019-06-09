#include "GUITextComponent.h"

#include "RenderManager.h"
#include "SingletonsManager.h"
#include "AtlasManager.h"
#include "Texture.h"
#include "PrimitiveMeshFactory.h"
#include "Entity.h"
#include "Log.h"

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity, uint32_t arg_maxItems)
    : GUIImageComponent(entity, arg_maxItems)
{ }

void GUITextComponent::loadFont(const std::string &fontFile)
{
    this->atlas = SingletonsManager::getInstance()->resolve<AtlasManager>()->getFont(fontFile);
}

void GUITextComponent::onStart()
{
    if (this->meshData.get() != nullptr)
        SingletonsManager::getInstance()->resolve<RenderManager>()->setupBufferSubData(this);
}

void GUITextComponent::setText(const std::string &text)
{
    if (text.size() > this->maxItems)
        throw "[ERROR] [GUITextComponent] - Text bigger than maxItems";
    else if (!text.empty())
    {
        PrimitiveMeshFactory meshFactory;
        std::vector<GUIVertexData> vertices;
        std::vector<uint32_t> indices;

        glm::vec2 offset(0.0f, 0.0f);
        int itemsCount = 0;
        for (char item : text)
        {
            const FontItem *atlasItem = static_cast<const FontItem *>(this->atlas->getItem(std::to_string(item)));
            if (atlasItem == nullptr)
            {
                Log::logMessage("'" + std::to_string(item) + "' does not exists in the loaded atlas");
                continue;
            }

            offset.y = -atlasItem->offset.y;
            
            if (item != ' ')
                meshFactory.createVerticesPlane2D(atlasItem->normalizedSize, atlasItem->uv, offset, vertices);

            offset.x += atlasItem->xAdvance * 2.0f;

            itemsCount++;
        }

        meshFactory.createPlaneIndices(indices, itemsCount);
        this->meshData = std::make_unique<MeshData<GUIVertexData>>(vertices, indices);

        SingletonsManager::getInstance()->resolve<RenderManager>()->setupBufferSubData(this);
    }
}

uint32_t GUITextComponent::getTextureId()
{
    return this->atlas->getTextureId();
}

} // namespace