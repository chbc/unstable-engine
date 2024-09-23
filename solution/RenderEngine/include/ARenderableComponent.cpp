#include "ARenderableComponent.h"
#include "MeshEditorProperty.h"

sre::ARenderableComponent::ARenderableComponent(Entity* entity) : AEntityComponent(entity), opaque(true)
{
	this->addEditorProperty(new MeshEditorProperty{ "MeshType", &this->meshData });
}

void sre::ARenderableComponent::setMeshData(MeshData* meshData)
{
	this->meshData = UPTR<MeshData>{ meshData };
}
