#include "CppUnitTest.h"

#include <engine/math/Vector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SRETests
{		
	TEST_CLASS(MathTests)
	{
	public:
		
		TEST_METHOD(AddOperationTest)
		{
			Vector v1(1, 2, 3);
			Vector v2(5, 4, 3);
			Vector v3 = v1 + v2;
			
			Assert::IsTrue(this->isVectorsEquals(v3, Vector(6, 6, 6)));
		}

		TEST_METHOD(SubtractOperationTest)
		{
			Vector v1(1, 2, 3);
			Vector v2(5, 4, 3);
			Vector v3 = v1 - v2;

			Assert::IsTrue(this->isVectorsEquals(v3, Vector(-4, -2, 0)));
		}

	private:

		bool isVectorsEquals(const Vector &v1, const Vector &v2)
		{
			return 
			(
				(v1.x == v2.x) &&
				(v1.y == v2.y) &&
				(v1.z == v2.z)
			);
		}

	};
}
