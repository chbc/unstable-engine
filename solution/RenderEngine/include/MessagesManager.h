#ifndef _MESSAGES_MANAGER_H_
#define _MESSAGES_MANAGER_H_

#include <unordered_map>
#include <functional>
#include <list>
#include "ASingleton.h"

#include "core_defines.h"

namespace sre
{

using Action = std::function<void(void*)>;

class MessagesManager : public ASingleton
{
private:
	// <type, callback>
	std::unordered_map<uint16_t, std::list<Action>> data;
	
public:
	template <typename T>
	void addListener(Action& callback);

	template <typename T>
	void removeListener(Action& callback);

	template <typename T>
	void notify(T* message) const;

friend class SingletonsManager;
};

}

#include "MessagesManager.tpp"

#endif
