#ifndef _I_SINGLETON_H_
#define _I_SINGLETON_H_

namespace sre
{

class ISingleton
{
protected:
    virtual void init() = 0;
    virtual void release() = 0;

friend class SingletonsManager;
};

}

#endif
