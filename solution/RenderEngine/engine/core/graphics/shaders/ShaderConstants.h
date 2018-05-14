#ifndef _SHADER_CONSTS_H_
#define _SHADER_CONSTS_H_

#include <string>
#include <unordered_map>

namespace sre
{

namespace ShaderFiles
{
    const std::string MAIN_H_V      = "../../shaders/main_h.vert";
    const std::string MAIN_IMPL_V   = "../../shaders/main_impl.vert";
    const std::string MAIN_H_F      = "../../shaders/main_h.frag";
    const std::string MAIN_IMPL_F   = "../../shaders/main_impl.frag";

    const std::string GUI_V = "../../shaders/gui.vert";
    const std::string GUI_F = "../../shaders/gui.frag";

    const std::string LIGHTS_H_V    = "../../shaders/lights_h.vert";
    const std::string LIGHTS_IMPL_V = "../../shaders/lights_impl.vert";
    const std::string LIGHTS_H_F    = "../../shaders/lights_h.frag";
    const std::string LIGHTS_IMPL_F = "../../shaders/lights_impl.frag";

    const std::string DIFFUSE_H_F       = "../../shaders/diffuse_h.frag";
    const std::string DIFFUSE_IMPL_F    = "../../shaders/diffuse_impl.frag";

    const std::string NORMAL_H_V    = "../../shaders/normal_h.vert";
    const std::string NORMAL_IMPL_V = "../../shaders/normal_impl.vert";
    const std::string NORMAL_H_F    = "../../shaders/normal_h.frag";
    const std::string NORMAL_IMPL_F = "../../shaders/normal_impl.frag";

    const std::string SPECULAR_H_F      = "../../shaders/specular_h.frag";
    const std::string SPECULAR_IMPL_F   = "../../shaders/specular_impl.frag";

    const std::string AMBIENT_OCCLUSION_H_F     = "../../shaders/ambientOcclusion_h.frag";
    const std::string AMBIENT_OCCLUSION_IMPL_F  = "../../shaders/ambientOcclusion_impl.frag";
}

namespace ShaderVariables
{
    namespace Names
    {
        const std::string VIEW_MATRIX       = "viewMatrix";
        const std::string PROJECTION_MATRIX = "projectionMatrix";
        const std::string MODEL_MATRIX      = "modelMatrix";
        const std::string CAMERA_POSITION   = "cameraPosition";
        const std::string MATERIAL_COLOR    = "materialColor";
        const std::string SHININESS         = "shininess";
        const std::string GUI_TEXTURE       = "guiTexture";
        const std::string DIFFUSE_TEXTURE   = "diffuseTexture";
        const std::string AO_TEXTURE        = "aoTexture";
        const std::string NORMAL_TEXTURE    = "normalTexture";
        const std::string SPECULAR_TEXTURE  = "specularTexture";

        const std::string AMBIENT_LIGHT_COLOR       = "lights.ambientLightColor";
        const std::string DIRECTIONAL_LIGHTS_COUNT  = "lights.directionalLightsCount";
        const std::string POINT_LIGHTS_COUNT        = "lights.pointLightsCount";
    }

    enum Type
    {
        VIEW_MATRIX,
        PROJECTION_MATRIX,
        MODEL_MATRIX,
        CAMERA_POSITION,

        MATERIAL_COLOR,
        SHININESS,

        GUI_TEXTURE,
        DIFFUSE_TEXTURE,
        AO_TEXTURE,
        NORMAL_TEXTURE,
        SPECULAR_TEXTURE,

        AMBIENT_LIGHT_COLOR,
        DIRECTIONAL_LIGHTS_COUNT,
        POINT_LIGHTS_COUNT
    };

    const std::unordered_map<ShaderVariables::Type, std::string> Map
    {
        { VIEW_MATRIX,                  Names::VIEW_MATRIX                  },
        { PROJECTION_MATRIX,            Names::PROJECTION_MATRIX            },
        { VIEW_MATRIX,                  Names::VIEW_MATRIX                  },
        { PROJECTION_MATRIX,            Names::PROJECTION_MATRIX            },
        { MODEL_MATRIX,                 Names::MODEL_MATRIX                 },
        { CAMERA_POSITION,              Names::CAMERA_POSITION              },
        { MATERIAL_COLOR,               Names::MATERIAL_COLOR               },
        { SHININESS,                    Names::SHININESS                    },
        { GUI_TEXTURE,                  Names::GUI_TEXTURE                  },
        { DIFFUSE_TEXTURE,              Names::DIFFUSE_TEXTURE              },
        { AO_TEXTURE,                   Names::AO_TEXTURE                   },
        { NORMAL_TEXTURE,               Names::NORMAL_TEXTURE               },
        { SPECULAR_TEXTURE,             Names::SPECULAR_TEXTURE             },
        { AMBIENT_LIGHT_COLOR,          Names::AMBIENT_LIGHT_COLOR          },
        { DIRECTIONAL_LIGHTS_COUNT,     Names::DIRECTIONAL_LIGHTS_COUNT     },
        { POINT_LIGHTS_COUNT,           Names::POINT_LIGHTS_COUNT           }
    };
}

} // namespace

#endif
