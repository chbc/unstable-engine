#include "GUITextComponent.h"

#include <engine/core/multimedia/textures/atlases/AtlasManager.h>
#include <engine/core/multimedia/textures/Texture.h>
#include <engine/core/graphics/meshData/PrimitiveMeshFactory.h>

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity, int maxItems) 
    : GUIImageComponent(entity, maxItems)
{ }

void GUITextComponent::loadFont(const std::string &fontFile)
{
	AtlasManager *atlasManager = AtlasManager::getInstance();
	this->atlas = atlasManager->getFont(fontFile);
}

void GUITextComponent::setText(const std::string &text)
{
	if (!text.empty() && (text.size() <= this->maxItems))
	{
		PrimitiveMeshFactory meshFactory;
		std::vector<GUIVertexData> vertices;
		std::vector<uint32_t> indices;

		glm::vec2 offset(0.0f, 0.0f);
		int itemsCount = 0;
		for (char item : text)
		{
			const FontItem *atlasItem = static_cast<const FontItem *>(this->atlas->getItem(std::to_string(item)));
			offset.y = -atlasItem->offset.y;

			if (item != ' ')
				meshFactory.createVerticesPlane2D(atlasItem->normalizedSize, atlasItem->uv, offset, vertices);

			offset.x += atlasItem->xAdvance * 2.0f;
			
			itemsCount++;
		}

		meshFactory.createPlaneIndices(indices, itemsCount);
		this->meshData = std::make_unique<MeshData<GUIVertexData>>(vertices, indices);
	}
    else
    {
        throw "[ERROR] [GUITextComponent] - Text is empty or is bigger than maxItems";
    }
}

uint32_t GUITextComponent::getTextureId()
{
	return this->atlas->getTextureId();
}

} // namespace
