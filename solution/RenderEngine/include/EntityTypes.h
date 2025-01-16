#pragma once

#include "core_defines.h"

#include <unordered_map>
#include <functional>
#include <string>

namespace sre
{

class Entity;
using CreateEntityObjectFunc = std::function<Entity* (std::string)>;

class EntityTypes
{
private:
    std::unordered_map<size_t, CreateEntityObjectFunc> typesMap;
    SRE_API static EntityTypes* instance;

public:
    static EntityTypes* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new EntityTypes;
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
        typesMap[key] = [](std::string name) { return new Type(name); };
    }

friend class Entity;
};

} // namespace
