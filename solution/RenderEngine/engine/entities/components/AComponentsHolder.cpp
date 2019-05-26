#include "AComponentsHolder.h"
#include "EComponentId.h"

namespace sre
{
	// ## namespace id
	//{
		template <typename TL>	std::size_t getComponentId();

		// Entity components
		template <> std::size_t getComponentId<class TransformComponent>() { return EComponentId::TRANSFORM; }
		template <> std::size_t getComponentId<class CameraComponent>() { return EComponentId::CAMERA; }
		template <> std::size_t getComponentId<class DirectionalLightComponent>() { return EComponentId::DIRECTIONAL_LIGHT; }
		template <> std::size_t getComponentId<class PointLightComponent>() { return EComponentId::POINT_LIGHT; }
		template <> std::size_t getComponentId<class MeshComponent>() { return EComponentId::MESH; }

		// Material components
		template <> std::size_t getComponentId<class ColorMaterialComponent>() { return EComponentId::COLOR_MATERIAL; }
		template <> std::size_t getComponentId<class LitMaterialComponent>() { return EComponentId::LIT_MATERIAL; }
		template <> std::size_t getComponentId<class DiffuseMaterialComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
		template <> std::size_t getComponentId<class NormalMaterialComponent>() { return EComponentId::NORMAL_MATERIAL; }
		template <> std::size_t getComponentId<class SpecularMaterialComponent>() { return EComponentId::SPECULAR_MATERIAL; }
		template <> std::size_t getComponentId<class AmbientOcclusionMaterialComponent>() { return EComponentId::AO_MATERIAL; }

		// GUI components
		template <> std::size_t getComponentId<class GUIImageComponent>() { return EComponentId::GUI_IMAGE; }
		template <> std::size_t getComponentId<class GUITextComponent>() { return EComponentId::GUI_TEXT; }

		// Renderer components
		template <> std::size_t getComponentId<class ColorRendererComponent>() { return EComponentId::COLOR_MATERIAL; }
		template <> std::size_t getComponentId<class LitRendererComponent>() { return EComponentId::LIT_MATERIAL; }
		template <> std::size_t getComponentId<class DiffuseRendererComponent>() { return EComponentId::DIFFUSE_MATERIAL; }
		template <> std::size_t getComponentId<class NormalRendererComponent>() { return EComponentId::NORMAL_MATERIAL; }
		template <> std::size_t getComponentId<class SpecularRendererComponent>() { return EComponentId::SPECULAR_MATERIAL; }
		template <> std::size_t getComponentId<class AORendererComponent>() { return EComponentId::AO_MATERIAL; }

	//} // namespace id

} // namespace sre
