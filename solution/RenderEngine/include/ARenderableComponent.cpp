#include "ARenderableComponent.h"
#include "MeshEditorProperty.h"

sre::ARenderableComponent::ARenderableComponent(Entity* entity) : AEntityComponent(entity), opaque(true)
{
	this->addEditorProperty(new MeshEditorProperty{ "Mesh", &this->mesh });
}
