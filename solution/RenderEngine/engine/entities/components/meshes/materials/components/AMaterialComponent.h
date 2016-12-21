#ifndef _A_MATERIAL_COMPONENT_H_
#define _A_MATERIAL_COMPONENT_H_

namespace sre
{

class Material;

class AMaterialComponent
{
protected:
	AMaterialComponent(Material *material) : material(material) {}
	Material *material;

public:
	virtual void init() =0;
};

}

#endif
