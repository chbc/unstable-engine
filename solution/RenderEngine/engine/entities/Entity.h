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

	template <typename T, typename... TArgs>
	T *addComponent(TArgs&&... mArgs)
	{
		T *newComponent{ nullptr };

		if (!AComponentsHolder<AEntityComponent>::hasComponent<T>())
		{
			newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
			AComponentsHolder<AEntityComponent>::addComponent(newComponent);
		}
		else
			throw "Can't add duplicate component!";

		return newComponent;
	}

	void update(uint32_t deltaTime);
	void addChild(Entity *child);
	inline uint32_t getChildrenCount() { return this->children.size(); }
	Entity *getChild(uint32_t index); // throws "Index out of range"

	TransformComponent *getTransform();

	void destroy();
	inline bool isAlive() { return this->alive; }

	friend class SceneManager;
	friend class ModelLoader;
};

} // namespace

// #include "Entity.tpp"

#endif
