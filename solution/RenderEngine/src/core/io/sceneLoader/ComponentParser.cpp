#define RYML_SINGLE_HDR_DEFINE_NOW
#include <rapidyaml/rapidyaml.hpp>

#include "ComponentParser.h"

#include "CameraComponent.h"
#include "MeshComponent.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

void ComponentParser::serialize(c4::yml::NodeRef& componentNode, AEntityComponent* component)
{
	componentNode |= ryml::MAP;
	componentNode["enabled"] << component->isEnabled();

	for (const SPTR<AEditorProperty>& property : component->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = componentNode[property->title.c_str()];
		std::ostringstream valueStream;

		bool isSequence = false;
		property->parseValue(valueStream, isSequence);

		if (isSequence)
		{
			propertyNode |= c4::yml::VAL_PLAIN;
		}
		propertyNode << valueStream.str();
	}
}

void ComponentParser::deserialize(c4::yml::ConstNodeRef& componentNode, Entity* entity)
{
	std::ostringstream keyStream;
	keyStream << componentNode.key();
	std::string type = keyStream.str();

	if (type == "TransformComponent")
	{
		c4::yml::ConstNodeRef positionNode = componentNode["Position"];
		glm::vec3 position;
		positionNode[0] >> position.x;
		positionNode[1] >> position.y;
		positionNode[2] >> position.z;
		entity->getTransform()->setPosition(position);
	}
	else if (type == "CameraComponent")
	{
		CameraComponent* camera = entity->addComponent<CameraComponent>();
		camera->setLookAt(glm::vec3{ 0.0f });
	}
	else if (type == "MeshComponent")
	{
		MeshData* meshData = PrimitiveMeshFactory().createPlane(1.0f, 1.0f);
		MeshComponent* mesh = entity->addComponent<MeshComponent>(meshData);
	}
}

} // namespace


/*
	propertyNode << *this->value;


	node |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	node.append_child() << ryml::fmt::real(*this->values[0], 5);
	node.append_child() << ryml::fmt::real(*this->values[1], 5);
	node.append_child() << ryml::fmt::real(*this->values[2], 5);


	color
	node |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	node.append_child() << ryml::fmt::real(this->values[0], 5);
	node.append_child() << ryml::fmt::real(this->values[1], 5);
	node.append_child() << ryml::fmt::real(this->values[2], 5);

	if (this->hasAlpha)
	{
		node.append_child() << ryml::fmt::real(this->values[3], 5);
	}
*/
