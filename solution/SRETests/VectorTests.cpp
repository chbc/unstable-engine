#include "CppUnitTest.h"

#include <engine/math/Vector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sre;

namespace SRETests
{		
	TEST_CLASS(VectorTests)
	{
	public:
		
		TEST_METHOD(AddOperationTest)
		{
			Vector v1(1, 2, 3);
			Vector v2(5, 4, 3);
			Vector v3 = v1 + v2;
			
			Assert::IsTrue(this->areVectorsEqual(v3, Vector(6, 6, 6)));
		}

		TEST_METHOD(SubtractOperationTest)
		{
			Vector v1(1, 2, 3);
			Vector v2(5, 4, 3);
			Vector v3 = v1 - v2;

			Assert::IsTrue(this->areVectorsEqual(v3, Vector(-4, -2, 0)));
		}

		TEST_METHOD(ScalarMultiplyOperationTest)
		{
			Vector v1(3, 5, 6);
			Vector v2 = v1 * 3;

			Assert::IsTrue(this->areVectorsEqual(v2, Vector(9, 15, 18)));
		}

		TEST_METHOD(LengthTest)
		{
			Vector v1(3, 4, 0);
			Assert::AreEqual(v1.length(), 5.0f);
		}

		TEST_METHOD(NormalizeTest)
		{
			Vector v1(3, 4, 0);
			Assert::IsTrue(this->areVectorsEqual(v1.normalize(), Vector(0.6f, 0.8f, 0.0f)));
		}

		TEST_METHOD(DotTest)
		{
			Vector v1(1, 2, 3);
			Vector v2(5, 4, 3);
			Assert::AreEqual(v1.dot(v2), 22.0f);
		}

		TEST_METHOD(TestCross)
		{
			Vector v1(1, 2, 3);
			Vector v2(5, 4, 3);
			Vector v3 = v1.cross(v2);
			Assert::IsTrue(this->areVectorsEqual(v3, Vector(-6, 12, -6)));
		}

		TEST_METHOD(DistanceTest)
		{
			Vector v1{3, 4, 0};
			Vector v2{6, 8, 0};
			Assert::AreEqual(v1.distance(v2), 5.0f);
		}

		TEST_METHOD(RotateTest)
		{
			Vector v1{2, 3, 4};
			Vector v2 = v1.rotate(Vector(0, 1, 0), 23);
			Assert::IsTrue(this->areVectorsAlmostEqual(v2, Vector(3.403934f, 3.0f, 2.900557f)));
		}

	private:

		bool areVectorsEqual(const Vector &v1, const Vector &v2)
		{
			return 
			(
				(v1.x == v2.x) &&
				(v1.y == v2.y) &&
				(v1.z == v2.z)
			);
		}

		bool areVectorsAlmostEqual(const Vector &v1, const Vector &v2)
		{
			const float TOL = 0.001f;
			return
			(
				(v1.x < v2.x + TOL) && (v1.x > v2.x - TOL) &&
				(v1.y < v2.y + TOL) && (v1.y > v2.y - TOL) &&
				(v1.z < v2.z + TOL) && (v1.z > v2.z - TOL)
			);
		}

	};
}
