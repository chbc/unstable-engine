#pragma once

#include "ABaseMaterial.h"
#include "core_defines.h"

#include <glm/glm.hpp>

namespace sre
{

class Material : public ABaseMaterial
{
private:
    glm::vec2 uvOffset{ 0.0f };
    glm::vec2 uvTiling{ 1.0f };
    bool castShadow{ false };

public:
    Material(std::string arg_filePath);

	SRE_API void setCastShadow(bool value);
    SRE_API bool getCastShadow();
	SRE_API void setReceivesLight(bool value);
	SRE_API bool getReceivesLight();
    SRE_API void setUVOffset(glm::vec2 uvOffset);
    SRE_API void setUVTiling(glm::vec2 tiling);
    SRE_API glm::vec2 getUVOffset();
    SRE_API glm::vec2 getUVTiling();
};

} // namespace
