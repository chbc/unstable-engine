#include "GUITextComponent.h"

#include <engine/core/graphics/RenderManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/multimedia/textures/atlases/AtlasManager.h>
#include <engine/core/multimedia/textures/Texture.h>
#include <engine/core/graphics/meshData/PrimitiveMeshFactory.h>
#include <engine/entities/Entity.h>
#include <engine/utils/Log.h>

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity, int maxItems) 
    : GUIImageComponent(entity, maxItems)
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

        if (this->getEntity()->isAlive())
            SingletonsManager::getInstance()->resolve<RenderManager>()->setupBufferSubData(this);
	}
}

uint32_t GUITextComponent::getTextureId()
{
	return this->atlas->getTextureId();
}

} // namespace
