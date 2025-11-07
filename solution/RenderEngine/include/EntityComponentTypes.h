#pragma once

#include "core_defines.h"

#include <unordered_map>
#include <vector>
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
    std::vector<const char*> classNames{ "   " };
    static EntityComponentTypes* instance;

public:
    SRE_API static EntityComponentTypes* getInstance();

    static void release();

    template<typename Type>
    void addType(const char* className)
    {
        classNames.push_back(className);

        size_t key = std::hash<std::string>{}(className);
        typesMap[key] = [](Entity* entity) { return new Type(entity); };
    }

    const std::vector<const char*>& getClassNames() const;

friend class AEntityComponent;
};

} // namespace
