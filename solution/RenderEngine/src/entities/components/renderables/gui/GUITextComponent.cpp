#include "GUITextComponent.h"

#include "RenderManager.h"
#include "SingletonsManager.h"
#include "AtlasManager.h"
#include "Texture.h"
#include "PrimitiveMeshFactory.h"
#include "Entity.h"
#include "MultimediaManager.h"

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
    this->atlas = SingletonsManager::getInstance()->get<AtlasManager>()->getFont(fontFile);

	GUIMeshData* plane = PrimitiveMeshFactory().createPlaneTopDown(glm::vec2(1.0f, 1.0f));
	this->mesh->meshData = UPTR<GUIMeshData>{ plane };
}

void GUITextComponent::onInit()
{
	if (this->mesh->meshData.get() != nullptr)
	{
		GUIMeshData* guiMeshData = static_cast<GUIMeshData*>(this->mesh->meshData.get());
		SingletonsManager::getInstance()->get<RenderManager>()->setupBufferSubData(guiMeshData);
	}
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
				MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();

				multimediaManager->logWarning("'" + std::to_string(item) + "' does not exists in the loaded atlas");
                continue;
            }

            offset.y = -atlasItem->offset.y;
            
            if (item != ' ')
                meshFactory.createVerticesPlane2D(atlasItem->normalizedSize, atlasItem->uv, offset, vertices);

            offset.x += atlasItem->xAdvance * 2.0f;

            itemsCount++;
        }

        meshFactory.createPlaneIndices(indices, itemsCount);

        GUIMeshData* guiMeshData = static_cast<GUIMeshData*>(this->mesh->meshData.get());

        guiMeshData->vertexData = vertices;
        guiMeshData->indices = indices;

        SingletonsManager::getInstance()->get<RenderManager>()->setupBufferSubData(guiMeshData);
    }
}

uint32_t GUITextComponent::getTextureId()
{
    return this->atlas->getTextureId();
}

} // namespace
