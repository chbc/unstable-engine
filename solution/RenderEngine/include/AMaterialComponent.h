#ifndef _A_MATERIAL_COMPONENT_H_
#define _A_MATERIAL_COMPONENT_H_

#include "core_defines.h"
#include "memory_aliases.h"
#include "AEditorProperty.h"

#include <vector>

#define DECLARE_MATERIAL_COMPONENT() \
    public: \
        static const char* CLASS_NAME; \
        const char* getClassName() override { return CLASS_NAME; }

#define IMPLEMENT_MATERIAL_COMPONENT(ComponentClass) \
    const char* ComponentClass::CLASS_NAME = #ComponentClass;

namespace sre
{

class Material;

class SRE_API AMaterialComponent
{

protected:
    Material * material;
    std::vector<SPTR<AEditorProperty>> editorProperties;

public:
    virtual ~AMaterialComponent() {}

    virtual const char* getClassName() = 0;

protected:
    AMaterialComponent(Material* arg_material);
    void addEditorProperty(AEditorProperty* editorProperty);

friend class MaterialEditorProperty;
};

}

#endif
