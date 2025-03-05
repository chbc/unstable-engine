#pragma once
#include "ASingleton.h"
#include "memory_aliases.h"
#include "core_defines.h"

#include <unordered_map>
#include <string>
#include <array>

namespace sre
{

constexpr size_t SINGLETONS_COUNT = 10;

class SingletonsManager
{
private:
    std::unordered_map<std::string, UPTR<ASingleton>> singletons;
    std::array<ASingleton*, SINGLETONS_COUNT> singletonsArray;
    size_t arrayIndex = 0;
    static UPTR<SingletonsManager> instance;

public:
    SingletonsManager();
    SRE_API static SingletonsManager* getInstance()
    {
        if (instance == nullptr)
        {
            throw "[SingletonsManager] - Instance not loaded!";
        }

        return instance.get();
    }

    template <typename T> T* get()
    {
        T* result = nullptr;
        std::string type = typeid(T).name();

        if (this->singletons.count(type) > 0)
            result = static_cast<T *>(this->singletons[type].get());
        else
            throw "Singleton not found: " + type;

        return result;
    }

    static bool isInitialized();

private:
    static SingletonsManager* loadInstance();
    void init();

    template <typename T> T* add()
    {
        std::string type = typeid(T).name();

        T* result = new T;
        this->singletons[type] = UPTR<ASingleton>{ result };
        this->singletonsArray[arrayIndex] = result;
        arrayIndex++;

        return result;
    }

    template <typename AbstractType, typename ConcretType>
    ConcretType* add()
    {
        ConcretType* result = nullptr;
        std::string type = typeid(AbstractType).name();

        result = new ConcretType;
        this->singletons[type] = UPTR<ASingleton>{ result };
        this->singletonsArray[arrayIndex] = result;
        arrayIndex++;

        return result;
    }

    void release();

friend class RenderEngine;
};

} // namespace
