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

    const std::string GUI_V = "../../shaders/gui/gui.vert";
    const std::string GUI_F = "../../shaders/gui/gui.frag";

    const std::string LIGHTS_H_V    = "../../shaders/lights/lights_h.vert";
    const std::string LIGHTS_IMPL_V = "../../shaders/lights/lights_impl.vert";
    const std::string LIGHTS_H_F    = "../../shaders/lights/lights_h.frag";
    const std::string LIGHTS_IMPL_F = "../../shaders/lights/lights_impl.frag";

    const std::string DIRECTIONAL_LIGHTS_H_V    = "../../shaders/lights/directional_lights_h.vert";
    const std::string DIRECTIONAL_LIGHTS_IMPL_V = "../../shaders/lights/directional_lights_impl.vert";
    const std::string DIRECTIONAL_LIGHTS_H_F    = "../../shaders/lights/directional_lights_h.frag";
    const std::string DIRECTIONAL_LIGHTS_IMPL_F = "../../shaders/lights/directional_lights_impl.frag";

    const std::string POINT_LIGHTS_H_V      = "../../shaders/lights/point_lights_h.vert";
    const std::string POINT_LIGHTS_IMPL_V   = "../../shaders/lights/point_lights_impl.vert";
    const std::string POINT_LIGHTS_H_F      = "../../shaders/lights/point_lights_h.frag";
    const std::string POINT_LIGHTS_IMPL_F   = "../../shaders/lights/point_lights_impl.frag";

    const std::string POINT_SHADOW_DEPTH_V = "../../shaders/shadows/point_shadow_depth.vert";
    const std::string POINT_SHADOW_DEPTH_F = "../../shaders/shadows/point_shadow_depth.frag";
    const std::string POINT_SHADOW_DEPTH_G = "../../shaders/shadows/point_shadow_depth.geom";

    const std::string DIRECTIONAL_SHADOW_DEPTH_V = "../../shaders/shadows/directional_shadow_depth.vert";
    const std::string DIRECTIONAL_SHADOW_DEPTH_F = "../../shaders/shadows/directional_shadow_depth.frag";

    const std::string DIFFUSE_H_F       = "../../shaders/diffuse/diffuse_h.frag";
    const std::string DIFFUSE_IMPL_F    = "../../shaders/diffuse/diffuse_impl.frag";

    const std::string NORMAL_H_V    = "../../shaders/normal/normal_h.vert";
    const std::string NORMAL_IMPL_V = "../../shaders/normal/normal_impl.vert";
    const std::string NORMAL_H_F    = "../../shaders/normal/normal_h.frag";
    const std::string NORMAL_IMPL_F = "../../shaders/normal/normal_impl.frag";

    const std::string NORMAL_DIRECTIONAL_H_V    = "../../shaders/normal/normal_directional_h.vert";
    const std::string NORMAL_DIRECTIONAL_IMPL_V = "../../shaders/normal/normal_directional_impl.vert";

    const std::string NORMAL_POINT_H_V      = "../../shaders/normal/normal_point_h.vert";
    const std::string NORMAL_POINT_IMPL_V   = "../../shaders/normal/normal_point_impl.vert";

    const std::string SPECULAR_H_F      = "../../shaders/specular/specular_h.frag";
    const std::string SPECULAR_IMPL_F   = "../../shaders/specular/specular_impl.frag";

    const std::string AMBIENT_OCCLUSION_H_F     = "../../shaders/ambientOcclusion/ambientOcclusion_h.frag";
    const std::string AMBIENT_OCCLUSION_IMPL_F  = "../../shaders/ambientOcclusion/ambientOcclusion_impl.frag";

    const std::string SHADOWS_DIRECTIONAL_H_V       = "../../shaders/shadows/shadows_directional_h.vert";
    const std::string SHADOWS_DIRECTIONAL_H_F       = "../../shaders/shadows/shadows_directional_h.frag";
    const std::string SHADOWS_DIRECTIONAL_IMPL_V    = "../../shaders/shadows/shadows_directional_impl.vert";
    const std::string SHADOWS_DIRECTIONAL_IMPL_F    = "../../shaders/shadows/shadows_directional_impl.frag";

    const std::string SHADOWS_POINT_H_V     = "../../shaders/shadows/shadows_point_h.vert";
    const std::string SHADOWS_POINT_H_F     = "../../shaders/shadows/shadows_point_h.frag";
    const std::string SHADOWS_POINT_IMPL_V  = "../../shaders/shadows/shadows_point_impl.vert";
    const std::string SHADOWS_POINT_IMPL_F  = "../../shaders/shadows/shadows_point_impl.frag";

	const std::string POST_PROCESSING_DEFAULT_V = "../../shaders/postProcessing/default.vert";
	const std::string POST_PROCESSING_DEFAULT_F = "../../shaders/postProcessing/default.frag";
}

namespace ShaderVariables
{
    namespace Names
    {
        const std::string VIEW_MATRIX           = "viewMatrix";
        const std::string PROJECTION_MATRIX     = "projectionMatrix";
        const std::string MODEL_MATRIX          = "modelMatrix";
        const std::string LIGHT_SPACE_MATRIX    = "lightSpaceMatrix";
        const std::string CAMERA_POSITION       = "cameraPosition";
        const std::string FAR_PLANE             = "farPlane";
        const std::string LIGHT_POSITION        = "lightPosition";
        const std::string MATERIAL_COLOR        = "materialColor";
        const std::string SHININESS             = "shininess";
        const std::string GUI_TEXTURE           = "guiTexture";
		const std::string SCREEN_TEXTURE		= "screenTexture";
        const std::string DIFFUSE_TEXTURE       = "diffuseTexture";
        const std::string AO_TEXTURE            = "aoTexture";
        const std::string NORMAL_TEXTURE        = "normalTexture";
        const std::string SPECULAR_TEXTURE      = "specularTexture";
        const std::string SHADOW_MAP            = "shadowMap";
        const std::string AMBIENT_LIGHT_COLOR   = "ambientLightColor";
    }

    enum Type
    {
        VIEW_MATRIX,
        PROJECTION_MATRIX,
        MODEL_MATRIX,
        LIGHT_SPACE_MATRIX,
        CAMERA_POSITION,
        FAR_PLANE,
        LIGHT_POSITION,

        MATERIAL_COLOR,
        SHININESS,

        GUI_TEXTURE,
		SCREEN_TEXTURE,
        DIFFUSE_TEXTURE,
        AO_TEXTURE,
        NORMAL_TEXTURE,
        SPECULAR_TEXTURE,
        SHADOW_MAP,

        AMBIENT_LIGHT_COLOR
    };

    const std::unordered_map<ShaderVariables::Type, std::string> Map
    {
        { VIEW_MATRIX,                  Names::VIEW_MATRIX                  },
        { PROJECTION_MATRIX,            Names::PROJECTION_MATRIX            },
        { VIEW_MATRIX,                  Names::VIEW_MATRIX                  },
        { PROJECTION_MATRIX,            Names::PROJECTION_MATRIX            },
        { MODEL_MATRIX,                 Names::MODEL_MATRIX                 },
        { LIGHT_SPACE_MATRIX,           Names::LIGHT_SPACE_MATRIX           },
        { CAMERA_POSITION,              Names::CAMERA_POSITION              },
        { FAR_PLANE,                    Names::FAR_PLANE                    },
        { LIGHT_POSITION,               Names::LIGHT_POSITION               },
        { MATERIAL_COLOR,               Names::MATERIAL_COLOR               },
        { SHININESS,                    Names::SHININESS                    },
        { GUI_TEXTURE,                  Names::GUI_TEXTURE                  },
		{ SCREEN_TEXTURE,               Names::SCREEN_TEXTURE               },
        { DIFFUSE_TEXTURE,              Names::DIFFUSE_TEXTURE              },
        { AO_TEXTURE,                   Names::AO_TEXTURE                   },
        { NORMAL_TEXTURE,               Names::NORMAL_TEXTURE               },
        { SPECULAR_TEXTURE,             Names::SPECULAR_TEXTURE             },
        { SHADOW_MAP,                   Names::SHADOW_MAP                   },
        { AMBIENT_LIGHT_COLOR,          Names::AMBIENT_LIGHT_COLOR          },
    };
}

} // namespace

#endif
