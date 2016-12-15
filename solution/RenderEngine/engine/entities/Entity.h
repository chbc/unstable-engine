#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "components/AComponentsHolder.h"
#include "components/transforms/TransformComponent.h"

namespace sre
{

/*!
	Class that represents a node of the scene.
*/
class Entity : public AComponentsHolder<AEntityComponent>
{
private:
	Entity *parent;
	std::vector<Entity *> children;

	TransformComponent *transform;

	bool alive;

	Entity();

public:
	~Entity();

	template <typename T> T *addComponent()
	{
		T *newComponent{ nullptr };

		if (!AComponentsHolder<AEntityComponent>::hasComponent<T>())
		{
			newComponent = new T{ this };
			AComponentsHolder<AEntityComponent>::addComponent(newComponent);
		}
		else
			throw "Can't add duplicate component!";

		return newComponent;
	}

	void update(uint32_t deltaTime);
	void addChild(Entity *child);

	TransformComponent *getTransform();

	void destroy();
	inline bool isAlive() { return this->alive; }

	friend class SceneManager;
};

} // namespace

// #include "Entity.tpp"

#endif
