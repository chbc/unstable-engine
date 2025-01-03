#pragma once

#include <unordered_map>
#include <functional>

namespace sre
{

class AEntityComponent;
class Entity;
using CreateObjectFunc = std::function<AEntityComponent* (Entity*)>;

class EntityComponentTypes
{
private:
    std::unordered_map<size_t, CreateObjectFunc> typesMap;
    static EntityComponentTypes* instance;

public:
    static EntityComponentTypes* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new EntityComponentTypes;
        }

        return instance;
    }

    static void release()
    {
        delete instance;
    }

    template<typename Type>
    void addType(const char* className)
    {
        size_t key = std::hash<std::string>{}(className);
        typesMap[key] = [](Entity* entity) { return new Type(entity); };
    }

friend class AEntityComponent;
};

} // namespace
