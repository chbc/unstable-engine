#ifndef _DEFAULT_GAME_VALUES_H_

#include "Blackboard.h"

namespace sre
{

class DefaultGameValues
{
private:
	static Blackboard blackboard;

public:
	template <typename T>
	const T operator [] (const std::string& key) const
	{
		return this->blackboard.Get<T>(key);
	}

	template <typename T>
	static void set(const std::string& key, T value)
	{
		this->blackboard.set(key, value);
	}

private:
	static void load();

friend class RenderEngine;
};

} // namespace

#endif
