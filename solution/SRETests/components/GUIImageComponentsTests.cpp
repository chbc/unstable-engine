#include <engine/tests/TestServicesProvider.h>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sre;

namespace SRETests
{
TEST_CLASS(GUIImageComponentTests)
{
public:
	static GUIImageComponent *component;
	static UPTR<Entity> entity;

	TEST_CLASS_INITIALIZE(SETUP)
	{
        /* ###
        MultimediaManager *multimediaManager = new MultimediaManager;
        multimediaManager->init();
		RenderManager::getInstance()->init();
        */

		entity = TestServicesProvider::getInstance()->createEntity();
		component = entity->addComponent<GUIImageComponent>("../../media/testTexture.png");
	}

	TEST_METHOD(GET_POSITION_1_1)
	{
		component->setUIPosition(glm::vec2(1.0f, 1.0f));
		glm::vec2 result = component->getUIPosition();
		Assert::IsTrue((result.x == 1.0f) && (result.y == 1.0f));
	}

	TEST_METHOD(SET_POSITION_1_1)
	{
		component->setUIPosition(glm::vec2(1.0f, 1.0f));
		glm::vec3 result = entity->getTransform()->getPosition();
		Assert::IsTrue((result.x == 1.0f) && (result.y == -1.0f));
	}
};

GUIImageComponent *GUIImageComponentTests::component = nullptr;
UPTR<Entity> GUIImageComponentTests::entity;
} // namespace
