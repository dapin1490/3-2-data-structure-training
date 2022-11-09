#include "C:/Users/dpgbu/Desktop/SAE/tool/visual studio/3-2 data structure training project/UnitTest01/pch.h"
#include "pch.h"
#include "CppUnitTest.h"
#include "../river waste project/main.cpp"
#include <algorithm>
#include "../river waste project/compl_system.h"

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
			�� �׽�Ʈ �޼��带 �����ϱ� ���� ����Ǵ� �޼���� methodName�� �����մϴ�.
			TEST_METHOD_INITIALIZE�� �׽�Ʈ Ŭ�������� �� ���� ������ �� ������
			�׽�Ʈ Ŭ������ �������� �����ؾ� �մϴ�.
			*/
			output << "���� �׽�Ʈ ���� �ð� : " << currentDateTime() << "\n\n";
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			// test method cleanup code
			/*
			�� �׽�Ʈ �޼��带 ������ �Ŀ� ����Ǵ� �޼���� methodName�� �����մϴ�.
			TEST_METHOD_CLEANUP�� �׽�Ʈ Ŭ�������� �� ���� ������ �� ������
			�׽�Ʈ Ŭ������ �������� �����ؾ� �մϴ�.
			*/
		}
		
		TEST_METHOD(BasicConstructorNMethod)
		{
			// test 1: ������ Ȯ��, �⺻���� �޼ҵ� ȣ�� Ȯ��
			int ws[5] = { 1, 0, 1, 0, 0 };
			complain c1 = complain("test.jpg", 20221029, 37.42, 126.79, 2, ws);
			complain c2 = complain("test2.jpg", 20221029, 37.42, 126.8, 2, "11000");
			accumed_compls a1 = accumed_compls(0);
			compl_system s1 = compl_system("11000");

			Assert::AreEqual(20221029, c1.get_date());
			Assert::AreEqual(true, std::equal(ws, ws + 5, c1.wastes, c1.wastes + 5));
			Assert::AreEqual(string("test2.jpg"), c2.get_name());
			Assert::AreEqual(0, a1.get_compls_size());
			Assert::AreEqual(0, a1.get_num());
		}

		TEST_METHOD(SystemOnTest)
		{
			// test 2: �ý��� ���� �� �����ڵ� �Է� �� ���� Ȯ�� : ������� �� �ż� �׽�Ʈ ���� �Ұ�
			compl_system s1;
			s1.system_on();

			string correct_code = "1111000000";
			string code = s1.get_acode();
			//Assert::AreEqual(correct_code, code);
		}
	};
}