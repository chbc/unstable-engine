#include "ABaseRenderer.h"
#include "Entity.h"
#include "MeshComponent.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"

namespace sre
{

ABaseRenderer::ABaseRenderer(ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWrapper)
    : shaderManager(arg_shaderManager), graphicsWrapper(arg_graphicsWrapper)
{
}

void ABaseRenderer::addMesh(MeshComponent* meshComponent)
{
    this->meshComponents.push_back(meshComponent);
    if (meshComponent->mesh->ebo == 0)
    {
        this->graphicsWrapper->createBuffers(meshComponent->mesh);
    }
}

void ABaseRenderer::removeDestroyedEntities()
{
    std::list<MeshComponent*>::iterator it;

    for (it = this->meshComponents.begin(); it != this->meshComponents.end(); )
    {
        MeshComponent* item = *it;
        if (!item->getEntity()->isAlive())
        {
            it = this->meshComponents.erase(it);
        }
        else
            ++it;
    }

    if (this->meshComponents.empty())
    {
		this->shaderManager->releaseShader(this->program);
	}
}

bool ABaseRenderer::removeMesh(MeshComponent* mesh)
{
    bool result = false;
    std::list<MeshComponent*>::iterator it;

    for (it = this->meshComponents.begin(); it != this->meshComponents.end(); ++it)
    {
        if (*it == mesh)
        {
            break;
        }
    }

    if (it != this->meshComponents.end())
    {
        this->meshComponents.erase(it);
        result = true;
    }

    if (this->meshComponents.empty())
    {
        this->shaderManager->releaseShader(this->program);
    }

    return result;
}

} // namespace
