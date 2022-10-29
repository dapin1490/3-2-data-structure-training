#include "pch.h"
#include "CppUnitTest.h"
#include "../river waste project/main.cpp"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest01
{
	TEST_CLASS(UnitTest01)
	{
	public:
		
		TEST_METHOD(BasicConstructorNMethod)
		{
			// test 1: 생성자 확인, 기본적인 메소드 호출 확인
			int ws[5] = { 1, 0, 1, 0, 0 };
			complain c1 = complain("test.jpg", 20221029, 37.42, 126.79, 2, ws);
			complain c2 = complain("test2.jpg", 20221029, 37.42, 126.8, 2, "11000");
			accumed_compls a1 = accumed_compls(0);
			compl_system s1 = compl_system(11000);

			Assert::AreEqual(20221029, c1.get_date());
			Assert::AreEqual(true, std::equal(ws, ws + 5, c1.wastes, c1.wastes + 5));
			Assert::AreEqual(string("test2.jpg"), c2.get_name());
			Assert::AreEqual(0, a1.get_compls_size());
			Assert::AreEqual(0, a1.get_num());
		}
	};
}