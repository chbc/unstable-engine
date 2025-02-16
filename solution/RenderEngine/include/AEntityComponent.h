#pragma once

#include "core_defines.h"
#include "memory_aliases.h"
#include <string>

#include "AEditorProperty.h"
#include "EntityComponentTypes.h"

namespace sre
{
class AEntityComponent;
class Entity;
class TransformComponent;

#define DECLARE_COMPONENT() \
    public: \
        static uint16_t ID; \
        static const uint16_t* BASE_ID; \
        static const char* CLASS_NAME; \
        const char* getClassName() override { return CLASS_NAME; } \
        uint16_t getId() override { return ID; } \
        void checkAndRefreshId() override { SetupChildId(); } \
        static void SetupChildId()  \
        {                           \
            if (BASE_ID != nullptr) \
            {                       \
                ID = *BASE_ID;      \
            }                       \
        }

#define IMPLEMENT_COMPONENT(ComponentClass) \
    const uint16_t* ComponentClass::BASE_ID = nullptr; \
    uint16_t ComponentClass::ID = AEntityComponent::generateId<ComponentClass>(#ComponentClass); \
    const char* ComponentClass::CLASS_NAME = #ComponentClass;

#define IMPLEMENT_CHILD_COMPONENT(ComponentClass, BaseComponentClass) \
    const uint16_t* ComponentClass::BASE_ID = nullptr; \
    uint16_t ComponentClass::ID = AEntityComponent::generateId<ComponentClass, BaseComponentClass>(#ComponentClass); \
    const char* ComponentClass::CLASS_NAME = #ComponentClass;

class SRE_API AEntityComponent
{
private:
    Entity* entity;
    bool enabled;
    std::vector<SPTR<AEditorProperty>> editorProperties;

private:
    static uint16_t Index;

public:
    AEntityComponent(Entity* arg_entity);
    virtual ~AEntityComponent();

    template <typename Type>
    static uint16_t generateId(const char* className)
    {
        EntityComponentTypes* types = EntityComponentTypes::getInstance();
        types->addType<Type>(className);

        return Index++;
    }

    template <typename Type, typename BaseType>
    static uint16_t generateId(const char* className)
    {
        EntityComponentTypes* types = EntityComponentTypes::getInstance();
        types->addType<Type>(className);
        Type::BASE_ID = &BaseType::ID;

        return 0;
    }

    static AEntityComponent* Create(const char* className, Entity* entity);

    inline Entity* getEntity() { return this->entity; }

    TransformComponent* getTransform();
    virtual const char* getClassName() = 0;

    void setEnabled(bool value);
    bool isEnabled() const;

protected:
    virtual uint16_t getId() = 0;
    virtual void checkAndRefreshId() = 0;

    virtual void onInit() {}
    virtual void onUpdate(float elapsedTime) {}
    virtual void onValueDeserialized() {}
    virtual void onValueChanged() {}
    void addEditorProperty(AEditorProperty* editorProperty);

private:
    void clone(AEntityComponent* result);

friend class Entity;
friend class EditorEntityProperties;
friend class ComponentParser;
};

} // namespace
