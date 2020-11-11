#ifndef _MESSAGES_MANAGER_H_
#define _MESSAGES_MANAGER_H_

#include <unordered_map>
#include <typeindex>
#include <functional>
#include <list>
#include "ASingleton.h"

namespace sre
{

using Action = std::function<void(void*)>;

class MessagesManager : public ASingleton
{
private:
	// <type, callback>
	std::unordered_map<std::type_index, std::list<Action>> data;
	
private:
	MessagesManager() = default;
	
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
