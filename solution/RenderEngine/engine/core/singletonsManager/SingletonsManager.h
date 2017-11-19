#ifndef _SINGLETONS_MANAGER_H_
#define _SINGLETONS_MANAGER_H_

#include "ISingleton.h"
#include <engine/utils/memory_aliases.h>
#include <unordered_map>
#include <string>

namespace sre
{

class SingletonsManager
{
private:
    std::unordered_map<std::string, UPTR<ISingleton>> singletons;
    static UPTR<SingletonsManager> instance;

    void release();

public:
    static SingletonsManager *getInstance()
    {
        if (instance.get() == nullptr)
            instance = std::make_unique<SingletonsManager>();

        return instance.get();
    }

    template <typename T> T* resolve()
    {
        T* result = nullptr;
        std::string type = typeid(T).name();

        if (this->singletons.count(type) > 0)
            result = static_cast<T *>(this->singletons[type].get());
        else
        {
            result = new T;
            this->singletons[type] = UPTR<ISingleton>{ result };
        }

        return result;
    }

    friend class RenderEngine;
};

} // namespace

#endif
