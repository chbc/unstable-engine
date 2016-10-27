#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <array>
#include <string>
#include "components/transforms/TransformComponent.h"
#include <engine/utils/memory_aliases.h>
#include <bitset>

namespace sre
{

constexpr std::size_t MAX_COMPONENTS{ 4 };

/*!
	Class that represents a node of the scene.
*/
class Entity
{
private:
#ifdef SRE_TESTS
public:
#endif
	Entity *parent;
	std::vector<Entity *> children;

	std::bitset<MAX_COMPONENTS> componentsBitset;
	std::array<AEntityComponent*, MAX_COMPONENTS> componentsArray;
	VECTOR_UPTR<AEntityComponent> components;

	TransformComponent *transform;

	bool alive;

	Entity();

public:
	~Entity();

	void addChild(Entity *child);

	TransformComponent *getTransform();

	void destroy();

	inline bool isAlive() { return this->alive; }

	template <typename T> T *addComponent();

	template <typename T> T *getComponent();

private:
	template <typename T> bool hasComponent();

	uint16_t generateComponentID();

	template <typename T>
	std::size_t getComponentID();
};

} // namespace

#include "Entity.tpp"

#endif
