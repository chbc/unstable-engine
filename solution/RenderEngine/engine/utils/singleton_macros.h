// declarations: instance, constructor, getInstance(), init() and release()
#ifndef _SINGLETON_MACROS_H_
#define _SINGLETON_MACROS_H_

#include "memory_aliases.h"

#define DECLARE_SINGLETON(className)			\
		private:								\
			static UPTR<className> instance;			\
			className();						\
		public:									\
			static className *getInstance();	\
			void init();						\
			void release();


// instance initialization and getInstance implementation
#define IMPLEMENT_SINGLETON(className)					\
		UPTR<className> className::instance = UPTR<className>(nullptr);			\
		className *className::getInstance()				\
		{												\
			if (instance.get() == nullptr)					\
				instance = UPTR<className>{ new className{} };				\
			return instance.get();							\
		}

#endif
