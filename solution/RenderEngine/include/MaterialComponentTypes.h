#pragma once

#include <unordered_map>
#include <functional>

namespace sre
{

class AMaterialComponent;
class Material;
using CreateMaterialObjectFunc = std::function<AMaterialComponent* (Material*)>;

class MaterialComponentTypes
{
private:
    std::unordered_map<int, CreateMaterialObjectFunc> typesMap;
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
        int key = std::hash<std::string>{}(className);
        typesMap[key] = [](Material* material) { return new Type(material); };
    }

friend class AMaterialComponent;
};

} // namespace
