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

void MatrixManager::push(const glm::mat4 &model)
{
    this->models.push(model);
}

void MatrixManager::push(float *matrix)
{
    glm::mat4 model = glm::make_mat4(matrix);
    this->models.push(model);
}

void MatrixManager::pop()
{
    this->models.pop();
}

void MatrixManager::setView(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up)
{
    this->view = glm::lookAt(position, lookTarget, up);
}

void MatrixManager::setView(Vector position, Vector lookTarget, Vector up)
{
    this->view = glm::lookAt(position.toVec3(), lookTarget.toVec3(), up.toVec3());
}

void MatrixManager::setProjection(float fov, float aspectRatio, float near, float far)
{
    this->projection = glm::perspective(fov, aspectRatio, near, far);
}

glm::mat4 MatrixManager::getModelMatrix()
{
	glm::mat4 result;

	std::stack<glm::mat4> modelMatrices = this->models;
	while (!modelMatrices.empty())
	{
		result *= modelMatrices.top();
		modelMatrices.pop();
	}

	return result;
}

glm::mat4 MatrixManager::getViewProjectionMatrix()
{
	return this->projection * this->view;
}

} // namespace
