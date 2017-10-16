#include "GUITextComponent.h"

#include <engine/core/multimedia/textures/atlases/AtlasManager.h>
#include <engine/core/multimedia/textures/Texture.h>
#include <engine/core/graphics/meshData/PrimitiveMeshFactory.h>

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity) : GUIImageComponent(entity, true)
{ }

void GUITextComponent::loadFont(const std::string &fontFile)
{
	AtlasManager *atlasManager = AtlasManager::getInstance();
	this->atlas = atlasManager->getFont(fontFile);
}

void GUITextComponent::setText(const std::string &text)
{
	if (!text.empty())
	{
		PrimitiveMeshFactory meshFactory;
		std::vector<GUIVertexData> vertices;
		std::vector<uint32_t> indices;

		float offset = 0;
		int itemsCount = 0;
		for (char item : text)
		{
			const FontItem *atlasItem = static_cast<const FontItem *>(this->atlas->getItem(std::to_string(item)));

			if (item != ' ')
				meshFactory.createVerticesPlane2D(atlasItem->normalizedSize, atlasItem->uv, offset, vertices);

			offset += (atlasItem->offset.x + atlasItem->xAdvance) * 1.75f;
			
			itemsCount++;
		}

		meshFactory.createPlaneIndices(indices, itemsCount);
		this->meshData = std::make_unique<MeshData<GUIVertexData>>(vertices, indices);
	}
}

uint32_t GUITextComponent::getTextureId()
{
	return this->atlas->getTextureId();
}

} // namespace
