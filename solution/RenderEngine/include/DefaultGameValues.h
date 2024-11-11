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
	static T get(const std::string& key)
	{
		return blackboard.get<T>(key);
	}

	template <typename T>
	static void set(const std::string& key, T value)
	{
		blackboard.set(key, value);
	}

private:
	static void load();
	static bool tryGetValue(const std::string& input, int& result);
	static bool tryGetValue(const std::string& input, float& result);

friend class RenderEngine;
};

} // namespace

#endif
