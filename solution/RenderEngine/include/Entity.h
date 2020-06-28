#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "AComponentsHolder.h"
#include "AEntityComponent.h"
#include "TransformComponent.h"

#include <vector>

namespace sre
{

// ### class TransformComponent;

/*!
    Class that represents a node of the scene.
*/
class Entity : public AComponentsHolder<AEntityComponent>
{
private:
    Entity *parent;
    std::vector<Entity *> children;

	TransformComponent* transform;

    bool alive;

private:
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

	SRE_API void addChild(Entity *child);
	SRE_API inline uint32_t getChildrenCount() { return this->children.size(); }
	SRE_API Entity *getChild(uint32_t index); // throws "Index out of range"
	SRE_API inline Entity *getParent() { return this->parent; }

	SRE_API TransformComponent *getTransform();

	SRE_API void destroy();
	SRE_API inline bool isAlive() { return this->alive; }

private:
	void onStart();
	void update(uint32_t deltaTime);

    friend class AEntityManager;
    friend class ModelLoader;

    friend class TestServicesProvider;
};

} // namespace

#endif
