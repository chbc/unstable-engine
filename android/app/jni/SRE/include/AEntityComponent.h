#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

#include "core_defines.h"
#include <stdint.h>

#define DECLARE_COMPONENT() \
    public: \
        static const uint16_t ID;

#define IMPLEMENT_COMPONENT(ClassName) \
    const uint16_t ClassName::ID = AEntityComponent::generateId();

namespace sre
{

class Entity;
class TransformComponent;

class SRE_API AEntityComponent
{
private:
    Entity* entity;

    static uint16_t Index;

public:
    AEntityComponent(Entity* arg_entity) : entity(arg_entity) { }

    inline Entity* getEntity() { return this->entity; }
    TransformComponent* getTransform();
    static uint16_t generateId();

protected:
    virtual void onStart() {}
    virtual void update(uint32_t deltaTime) {}


friend class Entity;
};

} // namespace

#endif
