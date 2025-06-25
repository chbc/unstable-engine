#include "GUITextComponent.h"
#include "RenderManager.h"
#include "SingletonsManager.h"
#include "AtlasManager.h"
#include "Texture.h"
#include "PrimitiveMeshFactory.h"
#include "FontEditorProperty.h"
#include "InputTextEditorProperty.h"
#include "Log.h"

namespace sre
{

IMPLEMENT_COMPONENT(GUITextComponent)

GUITextComponent::GUITextComponent(Entity *entity) : ABaseGUIComponent(entity)
{
	this->meshData = PrimitiveMeshFactory().createPlaneTopDown(glm::vec2(1.0f, 1.0f));
    this->addEditorProperty(new FontEditorProperty{ "Font", &this->atlas });
    this->addEditorProperty(new InputTextEditorProperty{ "Text", &this->text });
}

GUITextComponent::~GUITextComponent()
{
    delete this->meshData;
}

void GUITextComponent::setMaxItems(uint32_t arg_maxItems)
{
    this->maxItems = arg_maxItems;
}

void GUITextComponent::load(const std::string &fontFile)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->atlas = singletonsManager->get<AtlasManager>()->getFont(fontFile);
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
            const FontItem *atlasItem = static_cast<const FontItem *>(this->atlas->getItem(item));
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

        if (meshData->ebo > 0)
        {
            SingletonsManager::getInstance()->get<RenderManager>()->setupBufferSubData(meshData);
        }
    }

    this->text = text;
}

uint32_t GUITextComponent::getTextureId()
{
    return this->atlas->getTexture()->getId();
}

void GUITextComponent::onPropertyChanged()
{
    ABaseGUIComponent::onPropertyChanged();
    this->setText(this->text);
}

} // namespace
