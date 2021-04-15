
namespace sre
{
	template <typename T>
	void MessagesManager::addListener(Action& callback)
	{
		std::type_index type = typeid(T);
		std::list<Action>& callbackList = this->data[type];

		callbackList.push_back(callback);
	}

	template <typename T>
	void MessagesManager::removeListener(Action& callback)
	{
		std::type_index type = typeid(T);
		std::list<Action>& callbackList = this->data[type];

		callbackList.erase(callback);
		if (callbackList.empty())
		{
			this->data.erase(type);
		}
	}

	template <typename T>
	void MessagesManager::notify(T* message) const
	{
		std::type_index type = typeid(T);
		if (this->data.find(type) != this->data.end())
		{
			const std::list<Action>& callbackList = this->data.at(type);
			for (Action item : callbackList)
			{
				item(message);
			}
		}
	}

} // namespace
