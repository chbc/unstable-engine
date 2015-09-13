#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "ShaderConsts.h"
#include <vector>

namespace graphics
{
	class RenderManager;
};

namespace nodes
{
    class Mesh;
}

struct VertexData;

class Material
{
	protected:
		graphics::RenderManager *renderManager;
		unsigned int shaderProgram;
		float *ambient, *diffuse, *specular, shininess;

		inline unsigned int getShaderProgram() { return this->shaderProgram; }
		void loadShader(const std::string &vertexFile, const std::string &fragmentFile);

		virtual void apply(std::vector<VertexData> *vertexData, bool receiveLight) =0;

	public:
		Material();
		virtual ~Material();

		void setAmbient(float *ambient);
		void setDiffuse(float *diffuse);
		void setSpecular(float *specular);

	friend class graphics::RenderManager;
	friend class nodes::Mesh;
};

#endif
