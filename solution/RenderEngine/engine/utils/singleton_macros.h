// declarations: instance, constructor, getInstance(), init() and release()
#ifndef _SINGLETON_MACROS_H_
#define _SINGLETON_MACROS_H_

#include "memory_aliases.h"

#define DECLARE_SINGLETON(className)			\
		private:								\
			static SPTR<className> instance;			\
			className();						\
		public:									\
			static SPTR<className> getInstance();	\
			void init();						\
			void release();


// instance initialization and getInstance implementation
#define IMPLEMENT_SINGLETON(className)					\
		SPTR<className> className::instance = SPTR<className>(nullptr);			\
		SPTR<className> className::getInstance()				\
		{												\
			if (instance.get() == nullptr)					\
				instance = SPTR<className>{ new className{} };				\
			return instance;							\
		}

#endif
