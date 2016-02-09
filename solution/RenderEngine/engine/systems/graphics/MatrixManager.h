#ifndef _MATRIX_MANAGER_H_
#define _MATRIX_MANAGER_H_

#include <glm/matrix.hpp>
#include <stack>
#include <engine/math/Vector.h>

/*!
	Class to manage model, view and projection matrices.
*/
class MatrixManager
{
    private:
        std::stack<glm::mat4> models;
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 mvp;

	public:
	    MatrixManager();

        void push(const glm::mat4 &model);
        void push(float *matrix);
        void pop();

        void setView(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up);
        void setProjection(float fov, float aspectRatio, float near, float far);

        void setView(Vector position, Vector lookTarget, Vector up);

        void update();
        glm::mat4 getMVP();
};

#endif
