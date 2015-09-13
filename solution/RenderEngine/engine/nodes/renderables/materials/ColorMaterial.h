#ifndef _COLORMATERIAL_H_
#define _COLORMATERIAL_H_

#include "Material.h"

class ColorMaterial : public Material
{
	public:
		ColorMaterial();

		void apply(std::vector<VertexData> *vertexData, bool receiveLight);
};

#endif // _COLORMATERIAL_H_
