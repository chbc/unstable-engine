#ifndef _CAMERA_NODE_H_
#define _CAMERA_NODE_H_

#include <engine/entities/components/AEntityComponent.h>
#include <engine/math/Vector.h>

namespace sre
{
	
/*!
	Component that handles the camera on the scene.
*/
class CameraComponent : public AEntityComponent
{
	private:
		Vector lookAtTarget;
		Vector up;

	public:
		CameraComponent(Entity *entity);
		void setLookAt(const Vector &target);
};

} // namespace

#endif
