#ifndef _SINGLETONS_MANAGER_H_
#define _SINGLETONS_MANAGER_H_

#include "ASingleton.h"
#include "memory_aliases.h"
#include <unordered_map>
#include <string>

namespace sre
{

class SingletonsManager
{
private:
    std::unordered_map<std::string, UPTR<ASingleton>> singletons;
    static UPTR<SingletonsManager> instance;

public:
    SingletonsManager();
    static SingletonsManager* getInstance();

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

    /*
    template <typename T> T* resolve()
    {
        T* result = nullptr;
        std::string type = typeid(T).name();

        if (this->singletons.count(type) > 0)
            result = static_cast<T *>(this->singletons[type].get());
        else
        {
            result = new T;
            this->singletons[type] = UPTR<ASingleton>{ result };
        }

        return result;
    }
    */

private:
    void init();

    template <typename T> T* add()
    {
        std::string type = typeid(T).name();

        T* result = new T;
        this->singletons[type] = UPTR<ASingleton>{ result };

        return result;
    }

    template <typename AbstractType, typename ConcretType>
    ConcretType* add()
    {
        ConcretType* result = nullptr;
        std::string type = typeid(AbstractType).name();

        result = new ConcretType;
        this->singletons[type] = UPTR<ASingleton>{ result };

        return result;
    }

    void release();

friend class RenderEngine;
};

} // namespace

#endif
