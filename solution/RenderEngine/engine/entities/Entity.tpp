namespace sre
{

template <typename T>
T *Entity::addComponent()
{
	T *newComponent{ nullptr };

	if (!this->hasComponent<T>())
	{
		newComponent = new T{ this };
		UPTR<T> componentUptr{ newComponent };
		this->components.emplace_back(std::move(componentUptr));

		componentsArray[getComponentID<T>()] = newComponent;
		componentsBitset[getComponentID<T>()] = true;

		newComponent->init();
	}
	else
		throw "Can't add duplicate component!";

	return newComponent;
}

template <typename T>
T *Entity::getComponent()
{
	AEntityComponent *component{ nullptr };
	if (hasComponent<T>())
		component = componentsArray[this->getComponentID<T>()];
	else
		throw "Can't find component!";

	return static_cast<T*>(component);
}

template <typename T>
bool Entity::hasComponent()
{
	static_assert(std::is_base_of<AEntityComponent, T>::value, "T must be an AEntityComponent!");
	return this->componentsBitset[this->getComponentID<T>()];
}

template <typename T>
std::size_t Entity::getComponentID()
{
	static std::size_t typeID{ generateComponentID() };
	return typeID;
}

}
