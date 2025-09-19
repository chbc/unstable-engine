#pragma once

namespace sre
{

namespace EShaderComponent
{
	enum Type
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY
	};

	const char* getShaderComponentString(EShaderComponent::Type component);
}
} // namespace sre
