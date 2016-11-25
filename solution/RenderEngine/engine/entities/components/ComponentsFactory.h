#ifndef _COMPONENTS_FACTORY_H_
#define _COMPONENTS_FACTORY_H_

#include <engine/utils/singleton_macros.h>

namespace sre
{

class Entity;
class Material;

class ComponentsFactory
{
private:
	// ### AQUI
	template <typename T> static T *create(Entity *owner);
	template <typename T> static T *create(Material *owner);

};

} // namespace

#include "ComponentsFactory.tpp"

#endif
