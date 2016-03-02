#ifndef _OPENGL_API_H_
#define _OPENGL_API_H_

#include "AGraphicsWrapper.h"

namespace sre
{

class Mesh;

class OpenGLAPI : AGraphicsWrapper
{
	protected:
		OpenGLAPI() {}

		void init() override;
		void createVBO(Mesh *mesh) override;
		void createIBO(Mesh *mesh) override;
		void clearBuffer() override;
		void drawMesh(Mesh *mesh) override;

		static void TEST_drawTriangle();
		
	friend class AGraphicsWrapper;
};

} // namespace
#endif
