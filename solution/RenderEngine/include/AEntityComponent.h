#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

#include "core_defines.h"
#include <stdint.h>
#include <string>

#include "EditorVariable.h"

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

    std::vector<SPTR<EditorVariable>> editorVariables;

public:
    AEntityComponent(Entity* arg_entity) : entity(arg_entity) { }
    virtual ~AEntityComponent();

    template <typename T> void addEditorVariable(const char* name, TypeId::Type typeId, T* pointer)
    {
        this->editorVariables.push_back(SPTR<EditorVariable>(new EditorVariable{ name, typeId, pointer }));
    }

    inline Entity* getEntity() { return this->entity; }

    static uint16_t generateId();
    TransformComponent* getTransform();
    virtual const char* getClassName() = 0;

protected:
    virtual void onStart() {}
    virtual void update(uint32_t deltaTime) {}


friend class Entity;
friend class EditorEntityProperties;
};

} // namespace

#endif
