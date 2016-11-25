#ifndef _COLOR_MATERIAL_COMPONENT_H_
#define _COLOR_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <glm/vec3.hpp>


namespace sre
{

class ColorMaterialComponent : public AMaterialComponent
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse; 
	glm::vec3 specular;
	float shininess;

public:
	ColorMaterialComponent();

	// ### void apply(std::vector<VertexData> *vertexData, bool receiveLight);

	void setAmbient(const glm::vec3 &ambient);
	void setDiffuse(const glm::vec3 &diffuse);
	void setSpecular(const glm::vec3 &specular);
};

} // namespace
#endif
