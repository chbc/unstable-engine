#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <list>
#include <string>
#include <memory>

namespace sre
{

class SceneManager;
class Transform;
class AEntityComponent;

template<T>
using UPtr = std::unique_ptr<T>;

/*!
	Class that represents a node of the scene.
*/
class Entity
{
	protected:
		std::list<Entity *> children;
		Entity *parent;
		int id;

		Transform *transform;

		Entity();

	public:
		void addChild(Entity *child);

		Transform *getTransform();

		virtual void setPosition(Vector position);
		void setScale(Vector scale);
		void setRotation(Vector axis, float angle);

	friend class SceneManager;
};

} // namespace

#endif
