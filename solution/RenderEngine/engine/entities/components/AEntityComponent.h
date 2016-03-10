#ifndef _H_AENTITY_COMPONENT_H_
#define _H_AENTITY_COMPONENT_H_

namespace sre
{

class Entity;

class AEntityComponent
{
	private:
		Entity *entity;

	protected:
		virtual void init() {}
};

} // namespace

#endif
