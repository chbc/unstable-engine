#ifdef SRE_TEST
#include "TestServicesProvider.h"

namespace sre
{

IMPLEMENT_SINGLETON(TestServicesProvider)

TestServicesProvider::TestServicesProvider() {}

void TestServicesProvider::init() {}

void TestServicesProvider::release() {}

UPTR<Entity> TestServicesProvider::createEntity()
{
	UPTR<Entity> entity = UPTR<Entity>{ new Entity{} };
	return std::move(entity);
}

} // namespace
#endif
