#pragma once

#include <unordered_map>
#include <functional>

namespace sre
{

class AMaterialComponent;
class ABaseMaterial;
using CreateMaterialObjectFunc = std::function<AMaterialComponent* (ABaseMaterial*)>;

class MaterialComponentTypes
{
private:
    std::unordered_map<size_t, CreateMaterialObjectFunc> typesMap;
    static MaterialComponentTypes* instance;

public:
    static MaterialComponentTypes* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new MaterialComponentTypes;
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
        typesMap[key] = [](ABaseMaterial* material) { return new Type(material); };
    }

friend class AMaterialComponent;
};

} // namespace
