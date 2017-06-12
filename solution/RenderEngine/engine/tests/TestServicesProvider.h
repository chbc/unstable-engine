#ifdef SRE_TEST

#ifndef _TEST_SERVICES_PROVIDER_H_
#define _TEST_SERVICES_PROVIDER_H_

#include <engine/utils/singleton_macros.h>
#include <engine/entities/Entity.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/entities/components/meshes/MeshComponent.h>

namespace sre
{

class TestServicesProvider
{
DECLARE_SINGLETON(TestServicesProvider)

public:
	UPTR<Entity> createEntity();
};

} // namespace

#endif
#endif
