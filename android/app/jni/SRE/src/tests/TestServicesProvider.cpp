#ifdef SRE_TEST
#include "TestServicesProvider.h"

namespace sre
{

UPTR<Entity> TestServicesProvider::createEntity()
{
	UPTR<Entity> entity = UPTR<Entity>{ new Entity{} };
	return std::move(entity);
}

} // namespace
#endif
