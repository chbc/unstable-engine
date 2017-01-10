#ifndef _SHADER_CONSTS_H_
#define _SHADER_CONSTS_H_

#include <string>

namespace sre
{

namespace ShaderConsts
{
	// ### mudar para const
	static std::string COLOR_V = "../../shaders/color.vert";
	static std::string COLOR_F = "../../shaders/color.frag";

	static std::string DIFFUSE_V = "../../shaders/diffuseTexture.vert";
	static std::string DIFFUSE_F = "../../shaders/diffuseTexture.frag";

	static std::string SPECULAR_V = "../../shaders/specular.vert";
	static std::string SPECULAR_F = "../../shaders/specular.frag";

	static std::string TOON_V = "../../shaders/toon.vert";
	static std::string TOON_F = "../../shaders/toon.frag";
}

}

#endif
