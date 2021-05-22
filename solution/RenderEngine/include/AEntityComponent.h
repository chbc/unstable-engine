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

namespace sre
{

class Entity;
class TransformComponent;

class SRE_API AEntityComponent
{
private:
    Entity* entity;

    static uint16_t Index;

    std::vector<SPTR<AEditorProperty>> editorProperties;

public:
    AEntityComponent(Entity* arg_entity) : entity(arg_entity) { }
    ~AEntityComponent();


    inline Entity* getEntity() { return this->entity; }

    static uint16_t generateId();
    TransformComponent* getTransform();
    virtual const char* getClassName() = 0;

protected:
    virtual void onStart() {}
    virtual void update(uint32_t deltaTime) {}
    void addEditorProperty(AEditorProperty* editorProperty);


friend class Entity;
friend class EditorEntityProperties;
};

} // namespace

#endif
