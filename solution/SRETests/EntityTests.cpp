#include <engine/tests/TestServicesProvider.h>

#include "CppUnitTest.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sre;

namespace SRETests
{
TEST_CLASS(EntityTests)
{
public:
	TEST_METHOD(CreateEmptyEntityTest)
	{
		UPTR<Entity> entity = TestServicesProvider::createEntity();
		Assert::AreEqual(0u, entity->getChildrenCount());
		Assert::IsTrue(entity->hasComponent<TransformComponent>());

		auto functor = [&entity] { entity->getChild(0); };
		Assert::ExpectException<const char *>(functor);
	}

	TEST_METHOD(getExistingComponentTest)
	{
		UPTR<Entity> entity = TestServicesProvider::createEntity();
		TransformComponent *component = entity->getComponent<TransformComponent>();
		Assert::IsNotNull(component);
	}

	TEST_METHOD(getNotExistingComponentTest)
	{
		UPTR<Entity> entity = TestServicesProvider::createEntity();
		auto functor = [&entity] { entity->getComponent<MeshComponent>(); };
		Assert::ExpectException<const char *>(functor);
	}

	TEST_METHOD(AddExistingComponentTest)
	{
		UPTR<Entity> entity = TestServicesProvider::createEntity();
		auto functor = [&entity] { entity->addComponent<TransformComponent>(); };
		Assert::ExpectException<const char *>(functor);
	}

	TEST_METHOD(addChildTest)
	{
		UPTR<Entity> entity = TestServicesProvider::createEntity();
		UPTR<Entity> child  = TestServicesProvider::createEntity();
		entity->addChild(child.get());

		Assert::AreEqual(1u, entity->getChildrenCount());
		Assert::IsTrue(entity.get() == child->getParent());
	}

	TEST_METHOD(AddCameraComponentTest)
	{
		assertAddComponent<CameraComponent>();
	}

	TEST_METHOD(AddDirectionalLightComponentTest)
	{
		assertAddComponent<DirectionalLightComponent>();
	}

	TEST_METHOD(AddPointLightComponentTest)
	{
		assertAddComponent<PointLightComponent>();
	}

	TEST_METHOD(AddMeshComponentTest)
	{
		VECTOR_UPTR<VertexData> vertexData;
		std::vector<uint32_t> indices;
		assertAddComponent<MeshComponent>(vertexData, indices);
	}

private:
	template <typename T, typename... TParams>
	void assertAddComponent(TParams&&... parameters)
	{
		UPTR<Entity> entity = TestServicesProvider::getInstance()->createEntity();
		T *newComponent = entity->addComponent<T>(std::forward<TParams>(parameters)...);
		Assert::IsNotNull(newComponent);
		Assert::IsNotNull(newComponent->getEntity());
		Assert::IsTrue(entity->hasComponent<T>());
	}
};

} // namespace
