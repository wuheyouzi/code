#include <iostream>
using namespace std;

class Person10
{
public:
	static void func() // �����з���Ȩ��
	{
		m_A = 100;
		// s = "����"; // ���ɷ��ʷǾ�̬��Ա���޷���������
		cout << "static void func����" << endl;
	}

	static int m_A;
	string s;
};

int Person10::m_A = 0;

void test13()
{
	Person10 p;
	p.func();

	Person10::func();
}

int main11()
{
	test13();

	system("pause");

	return 0;
}