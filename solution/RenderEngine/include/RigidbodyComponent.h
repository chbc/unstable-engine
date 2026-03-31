#pragma once

#include "AEntityComponent.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API RigidbodyComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	glm::vec3 velocity{ 0.0f };
	glm::vec3 acceleration{ 0.0f };
	float mass{ 1.0f };
	float restitution{ 0.5f };
	bool useGravity{ true };

public:
	RigidbodyComponent(Entity* entity);
	void setVelocity(const glm::vec3& newVelocity);
	void applyForce(const glm::vec3& force);
	const glm::vec3& getVelocity() const;

friend class PhysicsManager;
};

} // namespace
