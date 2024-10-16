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
DECLARE_COMPONENT()

protected:
	TransformComponent *transform;
	glm::vec3 lookAtTarget;
	glm::vec3 up;

	glm::mat4 view;
	glm::mat4 projection;

private:
	bool isPerspective;
	float fov;
	bool isMainCamera;
	bool isApplicationCamera;
	float orthoWidth;
	float orthoHeight;

public:
	CameraComponent(Entity *entity);
	void setLookAt(const glm::vec3& target);
	void setPosition(const glm::vec3& position);
	glm::vec3 getPosition() const;

	glm::vec3 getLookAt() const;

	void setPerspectiveProjection(float arg_fov, float aspectRatio, float near, float far);
	void setOrthoProjection();
	void setOrthoProjection(float width, float height);
	void setMainCamera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

protected:
	void onValueChanged() override;

private:
	void updateView();

friend class RenderManager;
friend class EditorSceneViewport;
};

} // namespace

#endif
