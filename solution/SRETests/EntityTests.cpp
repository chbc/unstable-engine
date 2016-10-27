#include <engine/entities/Entity.h>
#include <engine/entities/components/cameras/CameraComponent.h>

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
			Entity entity;
			Assert::IsNull(entity.parent);
			Assert::IsNotNull(entity.transform);
			Assert::IsTrue(entity.children.empty());
			Assert::AreEqual(1, static_cast<int>(entity.components.size()));
		}

		TEST_METHOD(AddComponent)
		{
			Entity entity;
			CameraComponent *newComponent = entity.addComponent<CameraComponent>();

			Assert::AreEqual(2, static_cast<int>(entity.components.size()));
			Assert::IsNotNull(newComponent);
			Assert::IsNotNull(newComponent->entity);
		}

		TEST_METHOD(AddDuplicateComponent)
		{
			Entity entity;
			auto functor = [&entity] { entity.addComponent<TransformComponent>(); };
			Assert::ExpectException<const char *>(functor);
		}

		TEST_METHOD(getComponent)
		{
			Entity entity;
			entity.addComponent<CameraComponent>();
			CameraComponent *component = entity.getComponent<CameraComponent>();
			Assert::IsTrue(typeid(component) == typeid(CameraComponent *));
		}

		TEST_METHOD(getUnknowComponent)
		{
			Entity entity;
			auto functor = [&entity] { entity.getComponent<CameraComponent>(); };
			Assert::ExpectException<const char *>(functor);
		}

		TEST_METHOD(addChild)
		{
			Entity entity;
			Entity child;
			entity.addChild(&child);

			Assert::AreEqual(1, static_cast<int>(entity.children.size()));
			Assert::IsTrue(&entity == child.parent);
		}
	};
}
