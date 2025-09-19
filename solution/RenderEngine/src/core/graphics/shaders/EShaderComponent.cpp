#include "EShaderComponent.h"

namespace sre
{

namespace EShaderComponent
{

const char* getShaderComponentString(EShaderComponent::Type component)
{
	switch (component)
	{
		case EShaderComponent::VERTEX: return "Vertex";
		case EShaderComponent::FRAGMENT: return "Fragment";
		case EShaderComponent::GEOMETRY: return "Geometry";
		default: return "Unknown";
	}
}

} // namespace EShaderComponent
} // namespace sre
