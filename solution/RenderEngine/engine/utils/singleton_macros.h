// declarations: instance, constructor, getInstance(), init() and release()
#define DECLARE_SINGLETON(className)			\
		private:								\
			static className *instance;			\
			className();						\
		public:									\
			static className *getInstance();	\
			bool init();						\
			void release();


// instance initialization and getInstance implementation
#define IMPLEMENT_SINGLETON(className)					\
		className *className::instance = NULL;			\
		className *className::getInstance()				\
		{												\
			if (instance == NULL)						\
				instance = new className;				\
			return instance;							\
		}
