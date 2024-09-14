#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

#include "core_defines.h"
#include "memory_aliases.h"
#include <string>

#include "AEditorProperty.h"

#define DECLARE_COMPONENT() \
    public: \
        static const uint16_t ID; \
        static const char* CLASS_NAME; \
        const char* getClassName() override { return CLASS_NAME; }

#define IMPLEMENT_COMPONENT(ComponentClass) \
    const uint16_t ComponentClass::ID = AEntityComponent::generateId(); \
    const char* ComponentClass::CLASS_NAME = #ComponentClass;

namespace c4
{
    namespace yml
    {
        class ConstNodeRef;
    }
}

using SerializedNode = c4::yml::ConstNodeRef;

namespace sre
{

class Entity;
class TransformComponent;

class SRE_API AEntityComponent
{
private:
    Entity* entity;
    bool enabled;

    static uint16_t Index;

    std::vector<SPTR<AEditorProperty>> editorProperties;

public:
    AEntityComponent(Entity* arg_entity) : entity(arg_entity), enabled(true) { }
    ~AEntityComponent();


    inline Entity* getEntity() { return this->entity; }

    static uint16_t generateId();
    TransformComponent* getTransform();
    virtual const char* getClassName() = 0;

    void setEnabled(bool value);
    bool isEnabled() const;

protected:
    virtual void onStart() {}
    virtual void onUpdate(float elapsedTime) {}
    void addEditorProperty(AEditorProperty* editorProperty);
    virtual void deserialize(SerializedNode& node) {}

friend class Entity;
friend class EditorEntityProperties;
friend class ComponentParser;
};

} // namespace

#endif
