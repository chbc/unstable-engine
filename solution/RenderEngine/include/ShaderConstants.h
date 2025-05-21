#ifndef _SHADER_CONSTS_H_
#define _SHADER_CONSTS_H_

#include <string>
#include <unordered_map>

namespace sre
{

namespace ShaderFiles
{

#ifdef __ANDROID__
    const std::string BASE_FOLDER = "engine/es/shaders/";
#else
    const std::string BASE_FOLDER = "engine/shaders/";
#endif

    const std::string MAIN_H_V      = BASE_FOLDER + "main_h.vert";
    const std::string MAIN_IMPL_V   = BASE_FOLDER + "main_impl.vert";
    const std::string MAIN_H_F      = BASE_FOLDER + "main_h.frag";
    const std::string MAIN_IMPL_F   = BASE_FOLDER + "main_impl.frag";

    const std::string GUI_V = BASE_FOLDER + "gui/gui.vert";
    const std::string GUI_F = BASE_FOLDER + "gui/gui.frag";

    const std::string LIGHTS_H_V    = BASE_FOLDER + "lights/lights_h.vert";
    const std::string LIGHTS_IMPL_V = BASE_FOLDER + "lights/lights_impl.vert";
    const std::string LIGHTS_H_F    = BASE_FOLDER + "lights/lights_h.frag";
    const std::string LIGHTS_IMPL_F = BASE_FOLDER + "lights/lights_impl.frag";

    const std::string DIRECTIONAL_LIGHTS_H_F    = BASE_FOLDER + "lights/directional_lights_h.frag";
    const std::string DIRECTIONAL_LIGHTS_IMPL_F = BASE_FOLDER + "lights/directional_lights_impl.frag";

    const std::string POINT_LIGHTS_H_F      = BASE_FOLDER + "lights/point_lights_h.frag";
    const std::string POINT_LIGHTS_IMPL_F   = BASE_FOLDER + "lights/point_lights_impl.frag";

    const std::string POINT_SHADOW_DEPTH_V = BASE_FOLDER + "shadows/point_shadow_depth.vert";
    const std::string POINT_SHADOW_DEPTH_F = BASE_FOLDER + "shadows/point_shadow_depth.frag";
    const std::string POINT_SHADOW_DEPTH_G = BASE_FOLDER + "shadows/point_shadow_depth.geom";

    const std::string DIRECTIONAL_SHADOW_DEPTH_V = BASE_FOLDER + "shadows/directional_shadow_depth.vert";
    const std::string DIRECTIONAL_SHADOW_DEPTH_F = BASE_FOLDER + "shadows/directional_shadow_depth.frag";

    const std::string DIFFUSE_H_F       = BASE_FOLDER + "diffuse/diffuse_h.frag";
    const std::string DIFFUSE_IMPL_F    = BASE_FOLDER + "diffuse/diffuse_impl.frag";

    const std::string NORMAL_H_V    = BASE_FOLDER + "normal/normal_h.vert";
    const std::string NORMAL_IMPL_V = BASE_FOLDER + "normal/normal_impl.vert";
    const std::string NORMAL_H_F    = BASE_FOLDER + "normal/normal_h.frag";
    const std::string NORMAL_IMPL_F = BASE_FOLDER + "normal/normal_impl.frag";

    const std::string SPECULAR_H_F      = BASE_FOLDER + "specular/specular_h.frag";
    const std::string SPECULAR_IMPL_F   = BASE_FOLDER + "specular/specular_impl.frag";

    const std::string AMBIENT_OCCLUSION_H_F     = BASE_FOLDER + "ambientOcclusion/ambientOcclusion_h.frag";
    const std::string AMBIENT_OCCLUSION_IMPL_F  = BASE_FOLDER + "ambientOcclusion/ambientOcclusion_impl.frag";

    const std::string PBR_V = BASE_FOLDER + "pbr/pbr.vert";
    const std::string PBR_F = BASE_FOLDER + "pbr/pbr.frag";

    const std::string SECOND_TARGET_COLOR_F = BASE_FOLDER + "secondTarget/color.frag";

    const std::string SHADOWS_DIRECTIONAL_H_V       = BASE_FOLDER + "shadows/shadows_directional_h.vert";
    const std::string SHADOWS_DIRECTIONAL_H_F       = BASE_FOLDER + "shadows/shadows_directional_h.frag";
    const std::string SHADOWS_DIRECTIONAL_IMPL_V    = BASE_FOLDER + "shadows/shadows_directional_impl.vert";
    const std::string SHADOWS_DIRECTIONAL_IMPL_F    = BASE_FOLDER + "shadows/shadows_directional_impl.frag";

    const std::string SHADOWS_POINT_H_V     = BASE_FOLDER + "shadows/shadows_point_h.vert";
    const std::string SHADOWS_POINT_H_F     = BASE_FOLDER + "shadows/shadows_point_h.frag";
    const std::string SHADOWS_POINT_IMPL_V  = BASE_FOLDER + "shadows/shadows_point_impl.vert";
    const std::string SHADOWS_POINT_IMPL_F  = BASE_FOLDER + "shadows/shadows_point_impl.frag";

	// Post processing
	const std::string POST_PROCESSING_MAIN_V		= BASE_FOLDER + "postProcessing/main.vert";
	const std::string POST_PROCESSING_MAIN_H_F		= BASE_FOLDER + "postProcessing/main_h.frag";
	const std::string POST_PROCESSING_MAIN_IMPL_F	= BASE_FOLDER + "postProcessing/main_impl.frag";
	const std::string POST_PROCESSING_COMBINE_F		= BASE_FOLDER + "postProcessing/combine.frag";

	const std::string POST_PROCESSING_INVERSE_F			= BASE_FOLDER + "postProcessing/inverse.frag";
	const std::string POST_PROCESSING_GRAYSCALE_F		= BASE_FOLDER + "postProcessing/grayscale.frag";
	const std::string POST_PROCESSING_BLUR_F			= BASE_FOLDER + "postProcessing/blur.frag";
	const std::string POST_PROCESSING_PARTIAL_BLUR_F	= BASE_FOLDER + "postProcessing/partialBlur.frag";
	const std::string POST_PROCESSING_BLOOM_F			= BASE_FOLDER + "postProcessing/bloom.frag";
	const std::string POST_PROCESSING_HDR_F				= BASE_FOLDER + "postProcessing/hdr.frag";
    const std::string POST_PROCESSING_DOF_F             = BASE_FOLDER + "postProcessing/dof.frag";
    const std::string POST_PROCESSING_DEPTH_F           = BASE_FOLDER + "postProcessing/depth.frag";
    const std::string POST_PROCESSING_OUTLINE_F         = BASE_FOLDER + "postProcessing/outline.frag";
}

namespace ShaderVariables
{
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
        OUTLINE_COLOR,
        SHININESS,

        GUI_TEXTURE,
		SCREEN_TEXTURE,
        DIFFUSE_TEXTURE,
        AO_TEXTURE,
        NORMAL_TEXTURE,
        SPECULAR_TEXTURE,
        SHADOW_MAP,
        ALBEDO_TEXTURE,
        METALLIC_TEXTURE,
        ROUGHNESS_TEXTURE,

        IN_POSITION,
        IN_TEXTURE_COORDS,
        UV_OFFSET,
        UV_TILING,

        AMBIENT_LIGHT_COLOR
    };

    const std::unordered_map<ShaderVariables::Type, std::string> Map
    {
        { VIEW_MATRIX,                  "viewMatrix"        },
        { PROJECTION_MATRIX,            "projectionMatrix"  },
        { MODEL_MATRIX,                 "modelMatrix"       },
        { LIGHT_SPACE_MATRIX,           "lightSpaceMatrix"  },
        { CAMERA_POSITION,              "cameraPosition"    },
        { FAR_PLANE,                    "farPlane"          },
        { LIGHT_POSITION,               "lightPosition"     },
        { MATERIAL_COLOR,               "materialColor"     },
        { OUTLINE_COLOR,                "outlineColor"      },
        { SHININESS,                    "shininess"         },
        { GUI_TEXTURE,                  "guiTexture"        },
        { SCREEN_TEXTURE,               "screenTexture"     },
        { DIFFUSE_TEXTURE,              "diffuseTexture"    },
        { AO_TEXTURE,                   "aoTexture"         },
        { NORMAL_TEXTURE,               "normalTexture"     },
        { SPECULAR_TEXTURE,             "specularTexture"   },
		{ ALBEDO_TEXTURE,               "albedoTexture"     },
		{ METALLIC_TEXTURE,             "metallicTexture"   },
		{ ROUGHNESS_TEXTURE,            "roughnessTexture"  },
        { SHADOW_MAP,                   "shadowMap"         },
        { IN_POSITION,                  "in_position"       },
        { IN_TEXTURE_COORDS,            "in_textureCoords"  },
        { UV_OFFSET,                    "uvOffset"         },
        { UV_TILING,                    "uvTiling"         },
        { AMBIENT_LIGHT_COLOR,          "ambientLightColor" }
    };
}

} // namespace

#endif
