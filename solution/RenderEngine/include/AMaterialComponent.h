#ifndef _A_MATERIAL_COMPONENT_H_
#define _A_MATERIAL_COMPONENT_H_

#include "core_defines.h"
#include "memory_aliases.h"
#include "AEditorProperty.h"
#include "MaterialComponentTypes.h"
#include "EComponentId.h"

#include <vector>

#define DECLARE_MATERIAL_COMPONENT() \
    public: \
        static const EComponentId::Type ID; \
        static const char* CLASS_NAME; \
        const char* getClassName() override { return CLASS_NAME; } \
        EComponentId::Type getId() override { return ID; }

#define IMPLEMENT_MATERIAL_COMPONENT(ComponentClass, ComponentType) \
    const EComponentId::Type ComponentClass::ID = AMaterialComponent::generateId<ComponentClass>(#ComponentClass, EComponentId::ComponentType); \
    const char* ComponentClass::CLASS_NAME = #ComponentClass;

namespace sre
{

class Material;

class SRE_API AMaterialComponent
{

protected:
    Material* material;
    std::vector<SPTR<AEditorProperty>> editorProperties;

public:
    AMaterialComponent(Material* arg_material);
    virtual ~AMaterialComponent() { }
    virtual const char* getClassName() = 0;

protected:
    virtual EComponentId::Type getId() = 0;

    template <typename Type>
    static EComponentId::Type generateId(const char* className, EComponentId::Type ComponentType)
    {
        MaterialComponentTypes* types = MaterialComponentTypes::getInstance();
        types->addType<Type>(className);

        return ComponentType;
    }

	virtual void onPropertySerialized() {}
    virtual void onPropertyDeserialized() {}
    virtual void onPropertyChanged() {}
    void addEditorProperty(AEditorProperty* editorProperty);

    static AMaterialComponent* Create(const char* className, Material* material);

friend class MaterialEditorProperty;
friend class Material;
friend class MaterialLoader;
};

}

#endif
