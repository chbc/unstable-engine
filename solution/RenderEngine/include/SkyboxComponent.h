#pragma once

#include "MeshComponent.h"

namespace sre
{

class ABaseMaterial;

class SRE_API SkyboxComponent : public MeshComponent
{
DECLARE_COMPONENT()

public:
	SkyboxComponent(Entity* entity);

protected:
	void onPropertyChanged() override;
};

} // namespace
