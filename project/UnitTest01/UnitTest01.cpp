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
		TEST_METHOD_INITIALIZE(Initialize)
		{
			// method initialization code
			/*
			각 테스트 메서드를 실행하기 전에 실행되는 메서드로 methodName을 정의합니다.
			TEST_METHOD_INITIALIZE는 테스트 클래스에서 한 번만 정의할 수 있으며
			테스트 클래스의 범위에서 정의해야 합니다.
			*/
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			// test method cleanup code
			/*
			각 테스트 메서드를 실행한 후에 실행되는 메서드로 methodName을 정의합니다.
			TEST_METHOD_CLEANUP는 테스트 클래스에서 한 번만 정의할 수 있으며
			테스트 클래스의 범위에서 정의해야 합니다.
			*/
		}
		
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

		TEST_METHOD(SystemOnTest)
		{
			// test 2: 시스템 실행 시 지역코드 입력 후 파일 확인

		}
	};
}