#ifndef _NODE_H_
#define _NODE_H_

#include <list>
#include <string>
#include <engine/math/Transform.h>

class SceneManager;

namespace nodes
{

/*!
	Class that represents a node of the scene.
*/
class Node
{
	protected:
		std::list<Node *> children;
		Node *parent;
		int id;

		Transform *transform;

		Node();
		virtual ~Node();

	public:
		void addChild(Node *child);

		Transform *getTransform();

		virtual void setPosition(Vector position);
		void setScale(Vector scale);
		void setRotation(Vector axis, float angle);

	friend class ::SceneManager;
};

} // namespace node

#endif
