#ifndef _A_COMPONENTS_HOLDER_H_
#define _A_COMPONENTS_HOLDER_H_

#include "core_defines.h"

#include "memory_aliases.h"
#include <bitset>
#include <unordered_map>
#include "EComponentId.h"

namespace sre
{
	template <typename TL> SRE_API std::size_t getComponentId();

	constexpr size_t MAX_COMPONENTS{ EComponentId::SIZE };

	template <typename C>
	class AComponentsHolder
	{
	protected:
		std::bitset<MAX_COMPONENTS> componentsBitset;
		std::unordered_map<size_t, UPTR<C>> componentsMap;

	public:
		template <typename T> T* getComponent(); // throws "Can't find component"
		template <typename T> bool hasComponent();

	protected:
		template <typename T> void addComponent(T *newComponent);
		template <typename T> void removeComponent();
	private:
		template <typename TL>
		std::size_t getComponentId()
		{
			return sre::getComponentId<TL>();
		}
	};

} // namespace

#include "AComponentsHolder.tpp"

#endif
