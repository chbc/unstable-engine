#pragma once

#include <sstream>
#include <functional>

#include "core_defines.h"

namespace c4
{
	namespace yml
	{
		class NodeRef;
		class ConstNodeRef;
	}
}

class AEditorProperty;

#define DECLARE_PROPERTY() \
	protected: \
		void copy(AEditorProperty* destination) override;

#define IMPLEMENT_PROPERTY(PropertyClass) \
	void PropertyClass::copy(AEditorProperty* destination) \
	{ \
		PropertyClass* derivedProperty = static_cast<PropertyClass*>(destination); \
		*derivedProperty->value = *this->value; \
	}

namespace sre
{

class AEditorProperty
{
protected:
	std::string title;
	std::function<void(void)> onValueDeserializedCallback;
	std::function<void(void)> onValueChangedCallback;
	bool saved{ true };

public:
	AEditorProperty(const char* arg_title)
		: title(arg_title) { }

	virtual ~AEditorProperty() { }

	virtual void draw() = 0;
	virtual void serialize(c4::yml::NodeRef& propertyNode) = 0;
	virtual void deserialize(c4::yml::ConstNodeRef& propertyNode) = 0;
	bool isSaved();
	void setSaved();

protected:
	void onValueChanged();
	virtual void copy(AEditorProperty* destination) = 0;

friend class Entity;
friend class EntityParser;
friend class ComponentParser;
friend class MaterialLoader;
friend class SceneLoader;
friend class AEntityComponent;
friend class Material;
friend class AMaterialComponent;
};

} // namespace
