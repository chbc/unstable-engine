#pragma once

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
	glm::mat4 projection;
	glm::mat4 view;

private:
	bool isPerspective;
	float fov;
	bool isMainCamera;
	bool isApplicationCamera;
	float orthoWidth;
	float orthoHeight;

public:
	CameraComponent(Entity *entity);

	void setPerspectiveProjection(float arg_fov, float aspectRatio, float near, float far);
	void setOrthoProjection();
	void setOrthoProjection(float width, float height);
	void setMainCamera();
	void updateView();

	inline const glm::mat4& getProjectionMatrix() const;
	inline const glm::mat4& getViewMatrix() const;

protected:
	void onPropertyDeserialized() override;
	void onPropertyChanged() override;

friend class RenderManager;
friend class EditorSceneViewport;
};

} // namespace
