#include "MatrixManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

MatrixManager::MatrixManager()
{
    this->view = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);
}

void MatrixManager::setView(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up)
{
    this->view = glm::lookAt(position, lookTarget, up);
}

void MatrixManager::setProjection(float fov, float aspectRatio, float near, float far)
{
    this->projection = glm::perspective(fov, aspectRatio, near, far);
}

glm::mat4 MatrixManager::getViewMatrix()
{
	return this->view;
}

glm::mat4 MatrixManager::getProjectionMatrix()
{
	return this->projection;
}

} // namespace
