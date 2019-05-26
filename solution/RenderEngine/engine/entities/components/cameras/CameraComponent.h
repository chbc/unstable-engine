#ifndef _CAMERA_NODE_H_
#define _CAMERA_NODE_H_

#include <engine/entities/components/AEntityComponent.h>
#include <glm/vec3.hpp>

namespace sre
{

class TransformComponent;
	
/*!
	Component that handles the camera on the scene.
*/
class SRE_API CameraComponent : public AEntityComponent
{
private:
	TransformComponent *transform;
	glm::vec3 lookAtTarget;
	glm::vec3 up;

public:
	CameraComponent(Entity *entity);
	void setLookAt(const glm::vec3 &target);
	void setPosition(const glm::vec3 &position);

friend class RenderManager;
};

} // namespace

#endif
