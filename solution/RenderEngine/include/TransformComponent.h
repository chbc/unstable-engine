#pragma once

#include "AEntityComponent.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_mat.hpp>

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

	glm::mat4 rotation;
	glm::vec3 position{ 0.0f };
	glm::vec3 eulerAngles{ 0.0f };
	glm::vec3 scale{ 1.0f };

public:
	TransformComponent(Entity *entity);
	void setPosition(glm::vec3 arg_position);
	void translate(const glm::vec3& translation);
	void setScale(glm::vec3 arg_scale);
	void setRotation(const glm::vec3& axis, float angle);
	void rotate(const glm::vec3& axis, float angle);
	void rotate(glm::vec3 arg_eulerAngles);
	glm::vec3 getPosition() const;
	glm::quat getRotation() const;
	glm::vec3 getScale() const;
	void getPosition(float* result);
	void getRotation(float* result);
	void getScale(float* result);
	inline const glm::vec3 getInternalMatrixPosition() const;
	inline glm::vec3 getForward() const;
	inline glm::vec3 getRight() const;
	inline glm::vec3 getUp() const;
	inline const glm::mat4& getMatrix() const;

protected:
	void onPropertyDeserialized() override;
	void onPropertyChanged() override;

private:
	void updateMatrix();
	void propagateTransform();

friend class Entity;
friend class TransformEditorProperty;
};

} // namespace
