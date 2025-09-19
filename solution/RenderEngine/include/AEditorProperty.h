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
		virtual void onDraw() override; \
		virtual void onSerialize(c4::yml::NodeRef& propertyNode) override; \
		virtual void onDeserialize(c4::yml::ConstNodeRef& propertyNode) override; \
		virtual void copy(AEditorProperty* destination) override;

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

private:
	std::function<void(void)> onValueSerializedCallback;
	std::function<void(void)> onValueDeserializedCallback;
	std::function<void(void)> onValueChangedCallback;
	bool saved{ true };
	bool stored{ true };

public:
	AEditorProperty(const std::string& arg_title)
		: title(arg_title) { }

	virtual ~AEditorProperty() { }

	virtual void draw();
	virtual void serialize(c4::yml::NodeRef& propertyNode);
	virtual void deserialize(c4::yml::ConstNodeRef& propertyNode);
	bool isSaved();
	bool isStored() const;
	void setStored(bool value);

protected:
	virtual void onDraw() = 0;
	virtual void onSerialize(c4::yml::NodeRef& propertyNode) = 0;
	virtual void onDeserialize(c4::yml::ConstNodeRef& propertyNode) = 0;
	void onPropertyChanged();
	virtual void copy(AEditorProperty* destination) = 0;

friend class Entity;
friend class EntityParser;
friend class ComponentParser;
friend class MaterialLoader;
friend class SceneLoader;
friend class AEntityComponent;
friend class ABaseMaterial;
friend class AMaterialComponent;
};

} // namespace
