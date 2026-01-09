#pragma once

namespace sre
{

class ASingleton
{
protected:
    virtual void init() {};
	virtual void preRelease() {};
    virtual void release() {};

public:
	virtual ~ASingleton() = default;
	
friend class SingletonsManager;
};

}
