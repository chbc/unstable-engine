#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// ### #include "ShaderConsts.h"
#include <engine/entities/components/AComponentsHolder.h>
#include "components/AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>
#include "components/ColorMaterialComponent.h"
#include "components/DiffuseMaterialComponent.h"

namespace sre
{

// ### struct VertexData;

class Material : public AComponentsHolder<AMaterialComponent>
{
private:
	float shininess;

public:
	Material(float shininess = 15.0f);

	void setShininess(float shininess);
	float getShininess();

	template <typename T, typename... TArgs>
	T *addComponent(TArgs&&... mArgs)
	{
		T *newComponent{ nullptr };

		if (!AComponentsHolder<AMaterialComponent>::hasComponent<T>())
		{
			newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
			AComponentsHolder<AMaterialComponent>::addComponent(newComponent);
		}
		else
			throw "Can't add duplicate component!";

		return newComponent;
	}
	// ### void apply(std::vector<VertexData> *vertexData, bool receiveLight);

/* ###
friend class Mesh;
*/

friend class RenderManager;
friend class ColorMaterialComponent;
friend class ColorRenderer; // ###
};

} // namespace

#endif
