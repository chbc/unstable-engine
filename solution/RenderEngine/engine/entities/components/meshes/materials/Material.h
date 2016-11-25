#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// ### #include "ShaderConsts.h"
#include <engine/entities/components/AComponentsHolder.h>
#include "components/AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>

namespace sre
{

// ### struct VertexData;

class Material : public AComponentsHolder<AMaterialComponent>
{
private:
	unsigned int shaderProgram;

	inline unsigned int getShaderProgram() { return this->shaderProgram; }
	void loadShader(const std::string &vertexFile, const std::string &fragmentFile);

	// ### void apply(std::vector<VertexData> *vertexData, bool receiveLight);

public:
	Material();

private:

/* ###
friend class RenderManager;
friend class Mesh;
*/
};

} // namespace

#endif
