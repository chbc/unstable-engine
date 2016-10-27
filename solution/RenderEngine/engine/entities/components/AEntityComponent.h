#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

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
		AEntityComponent(Entity *entity) { this->entity = entity; }

	protected:
		virtual void init() {}

	friend class Entity;
};

} // namespace

#endif
