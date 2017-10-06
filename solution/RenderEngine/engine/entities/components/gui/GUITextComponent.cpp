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

		int tt = 0;
		for (char item : text)
		{
			// this->makeGliph(item);
			// ###
			const AtlasItem atlasItem = this->atlas->getItem(std::to_string(item));

			meshFactory.createVerticesPlane2D(glm::vec2(0.1f, 0.1f), atlasItem.uv, tt * 0.2f, vertices);
			tt++;
		}

		meshFactory.createPlaneIndices(indices, tt);
		this->meshData.emplace_back(new MeshData<GUIVertexData>{ vertices, indices });
	}
}

// ###
void GUITextComponent::makeGliph(int id)
{
	const AtlasItem atlasItem = this->atlas->getItem(std::to_string(id));
	this->meshData.emplace_back((PrimitiveMeshFactory()).createPlane2D(glm::vec2(0.5f, 0.5f), atlasItem.uv));
}

uint32_t GUITextComponent::getTextureId()
{
	return this->atlas->getTextureId();
}

} // namespace
