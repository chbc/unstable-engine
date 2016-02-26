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

void MatrixManager::setProjection(float fov, float aspectRatio, float near, float far)
{
    this->projection = glm::perspective(fov, aspectRatio, near, far);
}

void MatrixManager::setView(Vector position, Vector lookTarget, Vector up)
{
    this->view = glm::lookAt(position.toVec3(), lookTarget.toVec3(), up.toVec3());
}

void MatrixManager::update()
{
    glm::mat4 result = this->projection * this->view;

    std::stack<glm::mat4> currentModels;

    while (!this->models.empty())
    {
        currentModels.push(this->models.top());
        this->models.pop();
    }

    glm::mat4 model;
    while (!currentModels.empty())
    {
        model = currentModels.top();
        result *= model;
        this->models.push(model);
        currentModels.pop();
    }

    this->mvp = result;
}

glm::mat4 MatrixManager::getMVP()
{
    return this->mvp;
}

} // namespace