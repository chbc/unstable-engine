#ifndef _A_COMPONENTS_HOLDER_H_
#define _A_COMPONENTS_HOLDER_H_

#include <engine/utils/memory_aliases.h>
#include <bitset>
#include <array>

namespace sre
{

constexpr size_t MAX_COMPONENTS{ 4 };

template <typename C>
class AComponentsHolder
{
private:
	std::bitset<MAX_COMPONENTS> componentsBitset;
	std::array<C*, MAX_COMPONENTS> componentsArray;

protected:
	VECTOR_UPTR<C> components;

public:
	template <typename T> T *addComponent();
	template <typename T> T *getComponent();

private:
	template <typename T> bool hasComponent();
	template <typename T> std::size_t getComponentID();
	uint16_t generateComponentID();
};

} // namespace

#include "AComponentsHolder.tpp"

#endif
