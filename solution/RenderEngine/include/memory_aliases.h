#ifndef _MEMORY_ALIASES_H_
#define _MEMORY_ALIASES_H_

#include <memory>
#include <vector>
#include <list>

namespace sre
{

template<typename T>
using UPTR = std::unique_ptr<T>;

template<typename T>
using SPTR = std::shared_ptr<T>;

template<typename T>
using WPTR = std::weak_ptr<T>;

template<typename T>
using VECTOR_UPTR = std::vector<std::unique_ptr<T>>;

template<typename T>
using VECTOR_SPTR = std::vector<std::shared_ptr<T>>;

template<typename T>
using LIST_UPTR = std::list<std::unique_ptr<T>>;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // namespace

#endif
