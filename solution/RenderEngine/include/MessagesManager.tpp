
namespace sre
{
	
template <typename T>
void MessagesManager::addListener(Action* callback)
{
	uint16_t id = T::ID;
	std::list<Action*>& callbackList = this->data[id];

	callbackList.push_back(callback);
}

template <typename T>
void MessagesManager::removeListener(Action* callback)
{
	uint16_t id = T::ID;
	std::list<Action*>& callbackList = this->data[id];

	callbackList.remove(callback);
	if (callbackList.empty())
	{
		this->data.erase(id);
	}
}

template <typename T>
void MessagesManager::notify(T* message) const
{
	uint16_t id = T::ID;
	if (this->data.count(id) > 0)
	{
		const std::list<Action*>& callbackList = this->data.at(id);
		for (Action* item : callbackList)
		{
			(*item)(message);
		}
	}
}

} // namespace
