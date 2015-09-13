#ifndef _SPECULAR_MATERIAL_H_
#define _SPECULAR_MATERIAL_H_

#include "DiffuseMaterial.h"

class SpecularMaterial : public DiffuseMaterial
{
	public:
		SpecularMaterial(const std::string &fileName, float shininess = 10);

		void setShininess(float shininess);
};

#endif
