#include "AComponentsHolder.h"
#include "EComponentId.h"

namespace sre
{
	// ## namespace id
	//{
		template <typename TL> SRE_API std::size_t getComponentId();

		// Entity components
		template <> std::size_t SRE_API getComponentId<class TransformComponent>() { return EComponentId::TRANSFORM; }
		template <> std::size_t SRE_API getComponentId<class CameraComponent>() { return EComponentId::CAMERA; }
		template <> std::size_t SRE_API getComponentId<class DirectionalLightComponent>() { return EComponentId::DIRECTIONAL_LIGHT; }
		template <> std::size_t SRE_API getComponentId<class PointLightComponent>() { return EComponentId::POINT_LIGHT; }
		template <> std::size_t SRE_API getComponentId<class MeshComponent>() { return EComponentId::MESH; }
		template <> std::size_t SRE_API getComponentId<class PostProcessingComponent>() { return EComponentId::POST_PROCESSING; }

		// Material components
		template <> std::size_t SRE_API getComponentId<class ColorMaterialComponent>() { return EComponentId::COLOR_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class LitMaterialComponent>() { return EComponentId::LIT_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class DiffuseMaterialComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class NormalMaterialComponent>() { return EComponentId::NORMAL_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class SpecularMaterialComponent>() { return EComponentId::SPECULAR_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class AmbientOcclusionMaterialComponent>() { return EComponentId::AO_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class OutlineMaterialComponent>() { return EComponentId::SECOND_TARGET_COLOR_MATERIAL; }

		// GUI components
		template <> std::size_t SRE_API getComponentId<class GUIImageComponent>() { return EComponentId::GUI_IMAGE; }
		template <> std::size_t SRE_API getComponentId<class GUITextComponent>() { return EComponentId::GUI_TEXT; }

		// MeshRenderer components
		template <> std::size_t SRE_API getComponentId<class ColorRendererComponent>() { return EComponentId::COLOR_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class LitRendererComponent>() { return EComponentId::LIT_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class DiffuseRendererComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class NormalRendererComponent>() { return EComponentId::NORMAL_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class SpecularRendererComponent>() { return EComponentId::SPECULAR_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class AORendererComponent>() { return EComponentId::AO_MATERIAL; }
		template <> std::size_t SRE_API getComponentId<class OutlineRendererComponent>() { return EComponentId::SECOND_TARGET_COLOR_MATERIAL; }

	//} // namespace id

} // namespace sre
