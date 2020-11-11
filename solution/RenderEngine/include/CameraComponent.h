#ifndef _CAMERA_COMPONENT_H_
#define _CAMERA_COMPONENT_H_

#include "AEntityComponent.h"
#include <glm/matrix.hpp>

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

	glm::mat4 view;
	glm::mat4 projection;

public:
	CameraComponent(Entity *entity);
	void setLookAt(const glm::vec3 &target);
	void setPosition(const glm::vec3 &position);

	void setProjection(float fov, float aspectRatio, float near, float far);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

private:
	void updateView();

friend class RenderManager;
};

} // namespace

#endif
