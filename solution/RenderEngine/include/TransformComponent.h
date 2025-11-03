#pragma once

#include "AEntityComponent.h"
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

class Entity;

class SRE_API TransformComponent : public AEntityComponent
{
DECLARE_COMPONENT()

public:
	static glm::vec3 ZERO;
	static glm::vec3 UP;
	static glm::vec3 FRONT;
	static glm::vec3 RIGHT;

private:
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 worldMatrix{ 1.0f };

	glm::mat4 rotation{ 1.0 };
	glm::vec3 position{ 0.0f };
	glm::vec3 eulerAngles{ 0.0f };
	glm::vec3 scale{ 1.0f };

public:
	TransformComponent(Entity *entity);
	void setPosition(glm::vec3 arg_position);
	void translate(const glm::vec3& translation);
	void setScale(glm::vec3 arg_scale);
	void setRotation(const glm::vec3& axis, float angle);
	void setRotation(const glm::vec3& arg_eulerAngles);
	void setRotation(const glm::quat& arg_rotation);
	void setWorldMatrix(const glm::mat4& arg_worldMatrix);
	void setLookAtRotation(const glm::vec3& targetPosition);
	void rotate(const glm::vec3& axis, float angle);
	void rotate(glm::vec3 arg_eulerAngles);
	glm::vec3 getPosition() const;
	glm::quat getRotation() const;
	void getRotation(float& pitch, float& yaw, float& roll) const;
	glm::vec3 getScale() const;
	glm::vec3 getLocalPosition() const;
	glm::quat getLocalRotation() const;
	glm::vec3 getLocalScale() const;
	inline const glm::vec3 getInternalMatrixPosition() const;
	inline glm::vec3 getForward() const;
	inline glm::vec3 getRight() const;
	inline glm::vec3 getUp() const;
	inline const glm::mat4& getMatrix() const;
	void getValues(TransformComponent* resultTransform) const;

protected:
	void onPropertyDeserialized() override;
	void onPropertyChanged() override;

private:
	void updateLocalValues(const glm::mat4& arg_parentMatrix = glm::mat4{1.0f});
	void updateMatrix();
	void propagateTransform();

friend class Entity;
friend class TransformEditorProperty;
friend class SceneViewportGuizmos;
friend class AScene;
};

} // namespace
