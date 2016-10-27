#ifndef _MEMORY_ALIASES_H_
#define _MEMORY_ALIASES_H_

#include <memory>
#include <vector>

namespace sre
{

template<typename T>
using UPTR = std::unique_ptr<T>;

template<typename T>
using SPTR = std::shared_ptr<T>;

template<typename T>
using WPTR = std::weak_ptr<T>;

#define MAKE_UNIQUE std::make_unique
#define MAKE_SHARED std::make_shared

template<typename T>
using VECTOR_UPTR = std::vector<std::unique_ptr<T> >;

template<typename T>
using VECTOR_SPTR = std::vector<std::shared_ptr<T> >;

} // namespace

#endif
