#ifdef SRE_TEST

#ifndef _TEST_SERVICES_PROVIDER_H_
#define _TEST_SERVICES_PROVIDER_H_

#include <engine/entities/Entity.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/entities/components/renderables/gui/GUIImageComponent.h>
#include <engine/core/graphics/RenderManager.h>
#include <engine/core/multimedia/MultimediaManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>

namespace sre
{

class TestServicesProvider
{

public:
	static UPTR<Entity> createEntity();
};

} // namespace

#endif
#endif
