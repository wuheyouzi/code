#include <iostream>
using namespace std;

class Person10
{
public:
	static void func() // 可以有访问权限
	{
		m_A = 100;
		// s = "张三"; // 不可访问非静态成员，无法区分所属
		cout << "static void func调用" << endl;
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