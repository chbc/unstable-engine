#ifndef _BLACKBOARD_H_
#define _BLACKBOARD_H_

#include <unordered_map>
#include "memory_aliases.h"

namespace sre
{

class Blackboard
{
private:
	std::unordered_map<std::string, SPTR<void>> data;

public:
	template <typename T>
	T get(const std::string& key)
	{
		T* value = static_cast<T*>(this->data[key].get());

		return *value;
	}

	template <typename T>
	void set(std::string key, T value)
	{
		T* valuePtr = new T;
		*valuePtr = value;

		this->data[key] = SPTR<void>{ valuePtr };
	}
};

} // namespace

#endif
