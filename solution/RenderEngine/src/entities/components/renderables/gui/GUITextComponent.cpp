#include "GUITextComponent.h"
#include "RenderManager.h"
#include "SingletonsManager.h"
#include "AtlasManager.h"
#include "Texture.h"
#include "Entity.h"
#include "PrimitiveMeshFactory.h"
#include "Log.h"

namespace sre
{

IMPLEMENT_COMPONENT(GUITextComponent)

GUITextComponent::GUITextComponent(Entity *entity)
    : GUIImageComponent(entity), atlas(nullptr)
{
    this->setMaxItems(10);
}

void GUITextComponent::loadFont(const std::string &fontFile)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->atlas = singletonsManager->get<AtlasManager>()->getFont(fontFile);

	this->meshData = PrimitiveMeshFactory().createPlaneTopDown(glm::vec2(1.0f, 1.0f));
}

void GUITextComponent::onInit()
{
	if (this->meshData != nullptr)
	{
		SingletonsManager::getInstance()->get<RenderManager>()->setupBufferSubData(meshData);
	}
}

void GUITextComponent::setText(const std::string &text)
{
    if (text.size() > this->maxItems)
        throw "[ERROR] [GUITextComponent] - Text bigger than maxItems";
    else if (!text.empty())
    {
        PrimitiveMeshFactory meshFactory;

		meshData->vertexData.clear();
		meshData->indices.clear();

        glm::vec2 offset(0.0f, 0.0f);
        int itemsCount = 0;
        for (char item : text)
        {
            const FontItem *atlasItem = static_cast<const FontItem *>(this->atlas->getItem(std::to_string(item)));
            if (atlasItem == nullptr)
            {
				Log::LogWarning("'" + std::to_string(item) + "' does not exists in the loaded atlas");
                continue;
            }

            offset.y = -atlasItem->offset.y;
            
            if (item != ' ')
                meshFactory.createVerticesPlane2D(atlasItem->normalizedSize, atlasItem->uv, offset, meshData->vertexData);

            offset.x += atlasItem->xAdvance * 2.0f;

            itemsCount++;
        }

        meshFactory.createPlaneIndices(meshData->indices, itemsCount);

        SingletonsManager::getInstance()->get<RenderManager>()->setupBufferSubData(meshData);
    }
}

uint32_t GUITextComponent::getTextureId()
{
    return this->atlas->getTexture()->getId();
}

} // namespace
