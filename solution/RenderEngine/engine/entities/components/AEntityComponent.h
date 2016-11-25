#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

#include <stdint.h>

namespace sre
{

class Entity;

class AEntityComponent
{
private:
#ifdef SRE_TESTS
public:
#endif
	Entity *entity;

public:
	inline Entity *getEntity() { return this->entity; }

// protected:
	AEntityComponent(Entity *entity) { this->entity = entity; }
	virtual void init() {}
	virtual void update(uint32_t deltaTime) {}

friend class Entity;
// friend class AComponentsHolder<AEntityComponent>;

};

} // namespace

#endif
