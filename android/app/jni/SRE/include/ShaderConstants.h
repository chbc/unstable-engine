#ifndef _SHADER_CONSTS_H_
#define _SHADER_CONSTS_H_

#include <string>
#include <unordered_map>

namespace sre
{

namespace ShaderFiles
{

#ifdef __ANDROID__
    const std::string BASE_FOLDER = "shaders/es/";
#else
    const std::string BASE_FOLDER = "../../shaders/";
#endif

    const std::string MAIN_H_V      = BASE_FOLDER + "main_h.vert";
    const std::string MAIN_IMPL_V   = BASE_FOLDER + "main_impl.vert";
    const std::string MAIN_H_F      = BASE_FOLDER + "main_h.frag";
    const std::string MAIN_IMPL_F   = BASE_FOLDER + "main_impl.frag";

    const std::string GUI_V = BASE_FOLDER + "gui/gui.vert";
    const std::string GUI_F = BASE_FOLDER + "gui/gui.frag";

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

    const std::string DIFFUSE_H_F       = BASE_FOLDER + "diffuse/diffuse_h.frag";
    const std::string DIFFUSE_IMPL_F    = BASE_FOLDER + "diffuse/diffuse_impl.frag";

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

    const std::string SECOND_TARGET_COLOR_F = "../../shaders/secondTarget/color.frag";

    const std::string SHADOWS_DIRECTIONAL_H_V       = "../../shaders/shadows/shadows_directional_h.vert";
    const std::string SHADOWS_DIRECTIONAL_H_F       = "../../shaders/shadows/shadows_directional_h.frag";
    const std::string SHADOWS_DIRECTIONAL_IMPL_V    = "../../shaders/shadows/shadows_directional_impl.vert";
    const std::string SHADOWS_DIRECTIONAL_IMPL_F    = "../../shaders/shadows/shadows_directional_impl.frag";

    const std::string SHADOWS_POINT_H_V     = "../../shaders/shadows/shadows_point_h.vert";
    const std::string SHADOWS_POINT_H_F     = "../../shaders/shadows/shadows_point_h.frag";
    const std::string SHADOWS_POINT_IMPL_V  = "../../shaders/shadows/shadows_point_impl.vert";
    const std::string SHADOWS_POINT_IMPL_F  = "../../shaders/shadows/shadows_point_impl.frag";

	// Post processing
	const std::string POST_PROCESSING_MAIN_V		= "../../shaders/postProcessing/main.vert";
	const std::string POST_PROCESSING_MAIN_H_F		= "../../shaders/postProcessing/main_h.frag";
	const std::string POST_PROCESSING_MAIN_IMPL_F	= "../../shaders/postProcessing/main_impl.frag";
	const std::string POST_PROCESSING_COMBINE_F		= "../../shaders/postProcessing/combine.frag";

	const std::string POST_PROCESSING_INVERSE_F			= "../../shaders/postProcessing/inverse.frag";
	const std::string POST_PROCESSING_GRAYSCALE_F		= "../../shaders/postProcessing/grayscale.frag";
	const std::string POST_PROCESSING_BLUR_F			= "../../shaders/postProcessing/blur.frag";
	const std::string POST_PROCESSING_PARTIAL_BLUR_F	= "../../shaders/postProcessing/partialBlur.frag";
	const std::string POST_PROCESSING_BLOOM_F			= "../../shaders/postProcessing/bloom.frag";
	const std::string POST_PROCESSING_HDR_F				= "../../shaders/postProcessing/hdr.frag";
    const std::string POST_PROCESSING_DOF_F             = "../../shaders/postProcessing/dof.frag";
    const std::string POST_PROCESSING_DEPTH_F           = "../../shaders/postProcessing/depth.frag";
    const std::string POST_PROCESSING_OUTLINE_F         = "../../shaders/postProcessing/outline.frag";
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

        IN_POSITION,
        IN_TEXTURE_COORDS,

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
        { SHADOW_MAP,                   "shadowMap"         },
        { IN_POSITION,                  "in_position"       },
        { IN_TEXTURE_COORDS,            "in_textureCoords"  },
        { AMBIENT_LIGHT_COLOR,          "ambientLightColor" }
    };
}

} // namespace

#endif
