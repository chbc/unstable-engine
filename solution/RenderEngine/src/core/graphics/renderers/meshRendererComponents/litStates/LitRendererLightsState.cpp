#include "LitRendererLightsState.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "LitMaterialComponent.h"
#include "Material.h"

namespace sre
{

void LitRendererLightsState::preDraw(AGraphicsWrapper *graphicsWrapper)
{
    graphicsWrapper->enableVertexNormals();
}

void LitRendererLightsState::postDraw(AGraphicsWrapper *graphicsWrapper)
{
    graphicsWrapper->disableVertexNormals();
}

} // namespace
