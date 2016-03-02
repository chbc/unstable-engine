#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include <memory>

namespace sre
{

class Mesh;
class RenderManager;

class AGraphicsWrapper
{
	private:
		static std::unique_ptr<AGraphicsWrapper> instance;

	protected:
		AGraphicsWrapper() {}

		static AGraphicsWrapper *getInstance();

		virtual void init() = 0; // throws std::string
		virtual void createVBO(Mesh *mesh) =0;
		virtual void createIBO(Mesh *mesh) =0;
		virtual void drawMesh(Mesh *mesh) = 0;
		virtual void clearBuffer() =0;

		static void TEST_drawTriangle();

	friend class RenderManager;
};

} // namespace
#endif
