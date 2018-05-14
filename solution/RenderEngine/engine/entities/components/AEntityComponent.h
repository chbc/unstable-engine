#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

#include <stdint.h>

namespace sre
{

class Entity;
class TransformComponent;

class AEntityComponent
{
private:
    Entity *entity;

public:
    inline Entity *getEntity() { return this->entity; }
    TransformComponent *getTransform();

protected:
    AEntityComponent(Entity *entity) { this->entity = entity; }
    virtual void onStart() {}
    virtual void update(uint32_t deltaTime) {}

friend class Entity;

};

} // namespace

#endif
