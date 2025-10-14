#include "SkyboxComponent.h"
#include "ABaseMaterial.h"
#include "MaterialEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"

namespace sre
{
IMPLEMENT_COMPONENT(SkyboxComponent)

SkyboxComponent::SkyboxComponent(Entity* entity) : MeshComponent(entity)
{
}

} // namespace
