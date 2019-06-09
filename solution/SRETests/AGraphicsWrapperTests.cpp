#define SRE_TESTS
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>

#include "CppUnitTest.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sre;

namespace SRETests
{

TEST_CLASS(AGraphicsWrapperTests)
{
	public:
		TEST_CLASS_INITIALIZE(classInitialization)
		{
			Logger::WriteMessage("### Class initialization");
		}

		TEST_METHOD(initTest)
		{
			bool result = true;

			OpenGLAPI *wrapper = new OpenGLAPI;

			try
			{
				wrapper->init();
			}
			catch (std::string &message)
			{
				result = false;
				Logger::WriteMessage(message.c_str());
			}

			delete wrapper;

			Assert::IsTrue(result);

			delete wrapper;
		}
};

}
