#include <iostream>
using namespace std;

class Person06
{
public:
	// 传统方法
	/*Person06(int a, int b, int c)
	{
		m_A = a;
		m_B = b;
		m_C = c;
	}*/

	// 初始化列表初始化属性
	Person06(int a, int b, int c) :m_A(a), m_B(b), m_C(c)
	{

	}
	int m_A;
	int m_B;
	int m_C;
};

void test09()
{
	// Person06(10, 20, 30);

	Person06 p(30, 20, 10);

	cout << "m_A = " << p.m_A << endl;
	cout << "m_B = " << p.m_B << endl;
	cout << "m_C = " << p.m_C << endl;
}

int main06()
{
	test09();

	system("pause");

	return 0;
}