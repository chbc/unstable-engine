#ifndef _MATRIX_MANAGER_H_
#define _MATRIX_MANAGER_H_

#include <glm/matrix.hpp>

namespace sre
{

/*!
	Class to manage model, view and projection matrices.
*/
class MatrixManager
{
    private:
        glm::mat4 view;
        glm::mat4 projection;

	public:
	    MatrixManager();

        void setView(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up);
        void setProjection(float fov, float aspectRatio, float near, float far);

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
};

} // namespace
#endif
