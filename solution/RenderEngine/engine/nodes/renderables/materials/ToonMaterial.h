#ifndef _TOON_MATERIAL_H_
#define _TOON_MATERIAL_H_

#include "DiffuseMaterial.h"

class ToonMaterial : public DiffuseMaterial
{
	private:
		int layersCount;

	public:
		ToonMaterial(const std::string &fileName, int layersCount = 3);
};

#endif
