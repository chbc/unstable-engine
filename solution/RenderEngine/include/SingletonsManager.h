#pragma once
#include "ASingleton.h"
#include "memory_aliases.h"
#include "core_defines.h"

#include <unordered_map>
#include <string>

namespace sre
{

constexpr size_t SINGLETONS_COUNT = 10;

class SingletonsManager
{
private:
    std::unordered_map<std::size_t, UPTR<ASingleton>> singletons;
    ASingleton* singletonsArray[SINGLETONS_COUNT];
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

        size_t key = typeid(T).hash_code();

        if (this->singletons.count(key) > 0)
        {
            result = static_cast<T*>(this->singletons[key].get());
        }
        else
        {
            throw "Singleton not found!";
        }

        return result;
    }

    static bool isInitialized();

private:
    static SingletonsManager* loadInstance();
    void init();

    template <typename T> T* add()
    {
        T* result = new T;

        size_t key = typeid(T).hash_code();
        this->singletons[key] = UPTR<ASingleton>{ result };
        this->singletonsArray[arrayIndex] = result;
        arrayIndex++;

        return result;
    }

    template <typename AbstractType, typename ConcretType>
    ConcretType* add()
    {
        ConcretType* result = nullptr;
        size_t key = typeid(AbstractType).hash_code();

        result = new ConcretType;
        this->singletons[key] = UPTR<ASingleton>{ result };
        this->singletonsArray[arrayIndex] = result;
        arrayIndex++;

        return result;
    }

    void release();

friend class RenderEngine;
};

} // namespace
