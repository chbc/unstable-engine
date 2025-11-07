#include "EntityComponentTypes.h"

namespace sre
{

EntityComponentTypes* EntityComponentTypes::instance = nullptr;

EntityComponentTypes* EntityComponentTypes::getInstance()
{
    if (instance == nullptr)
    {
        instance = new EntityComponentTypes;
    }

    return instance;
}

void EntityComponentTypes::release()
{
	delete instance;
}

const std::vector<const char*>& EntityComponentTypes::getClassNames() const
{
    return this->classNames;
}

}
