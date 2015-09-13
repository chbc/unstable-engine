#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_

#include "Material.h"
#include "textures/Texture.h"

#include <vector>

class DiffuseMaterial : public Material
{
	private:
        std::vector<Texture *> textures;

	protected:
		void loadTexture(const std::string &fileName);

		void apply(std::vector<VertexData> *vertexData, bool receiveLight);

	public:
		DiffuseMaterial(const std::string &fileName);
		virtual ~DiffuseMaterial();

		unsigned int getTextureID(int index = 0);
};

#endif
